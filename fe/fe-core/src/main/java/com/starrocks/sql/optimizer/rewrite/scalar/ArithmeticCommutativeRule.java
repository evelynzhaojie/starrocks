// This file is licensed under the Elastic License 2.0. Copyright 2021 StarRocks Limited.

package com.starrocks.sql.optimizer.rewrite.scalar;

import com.google.common.collect.ImmutableMap;
import com.google.common.collect.Lists;
import com.starrocks.analysis.Expr;
import com.starrocks.catalog.Function;
import com.starrocks.catalog.FunctionSet;
import com.starrocks.sql.optimizer.operator.OperatorType;
import com.starrocks.sql.optimizer.operator.scalar.BinaryPredicateOperator;
import com.starrocks.sql.optimizer.operator.scalar.CallOperator;
import com.starrocks.sql.optimizer.operator.scalar.ScalarOperator;
import com.starrocks.sql.optimizer.rewrite.ScalarOperatorRewriteContext;

import java.util.Map;

public class ArithmeticCommutativeRule extends BottomUpScalarOperatorRewriteRule {
    // Don't support DIVIDE, because DIVIDE will use double type, Double is not efficient and will lose precision
    private static final Map<String, String> LEFT_COMMUTATIVE_MAP = ImmutableMap.<String, String>builder()
            .put(FunctionSet.ADD, FunctionSet.SUBTRACT)
            .put(FunctionSet.SUBTRACT, FunctionSet.ADD)
            .put(FunctionSet.DIVIDE, FunctionSet.MULTIPLY)
            .put(FunctionSet.YEARS_ADD, FunctionSet.YEARS_SUB)
            .put(FunctionSet.YEARS_SUB, FunctionSet.YEARS_ADD)
            .put(FunctionSet.MONTHS_ADD, FunctionSet.MONTHS_SUB)
            .put(FunctionSet.MONTHS_SUB, FunctionSet.MONTHS_ADD)
            .put(FunctionSet.DAYS_ADD, FunctionSet.DAYS_SUB)
            .put(FunctionSet.DAYS_SUB, FunctionSet.DAYS_ADD)
            .put(FunctionSet.ADDDATE, FunctionSet.SUBDATE)
            .put(FunctionSet.SUBDATE, FunctionSet.ADDDATE)
            .put(FunctionSet.DATE_ADD, FunctionSet.DATE_SUB)
            .put(FunctionSet.DATE_SUB, FunctionSet.DATE_ADD)
            .build();

    private static final Map<String, String> RIGHT_COMMUTATIVE_MAP = ImmutableMap.<String, String>builder()
            .put(FunctionSet.ADD, FunctionSet.SUBTRACT)
            .put(FunctionSet.SUBTRACT, FunctionSet.SUBTRACT)
            .build();

    @Override
    public ScalarOperator visitBinaryPredicate(BinaryPredicateOperator predicate,
                                               ScalarOperatorRewriteContext context) {
        // Has been normalize, variable must be right
        if (!predicate.getChild(1).isConstant() || !OperatorType.CALL.equals(predicate.getChild(0).getOpType())) {
            return predicate;
        }

        // Only handle expression like `Variable * Constant = Constant`
        CallOperator call = (CallOperator) predicate.getChild(0);
        if (null == call.getFunction() || call.getFunction().getReturnType().isDecimalOfAnyVersion() ||
                !LEFT_COMMUTATIVE_MAP.containsKey(call.getFunction().getFunctionName().toString())) {
            return predicate;
        }

        ScalarOperator s1 = call.getChild(0);
        ScalarOperator s2 = call.getChild(1);
        ScalarOperator result = predicate.getChild(1);

        if (s1.isVariable() && s2.isConstant()) {
            String fnName = LEFT_COMMUTATIVE_MAP.get(call.getFunction().getFunctionName().toString());
            Function fn = findArithmeticFunction(call, fnName);
            CallOperator n = new CallOperator(fnName, fn.getReturnType(), Lists.newArrayList(result, s2), fn);
            return new BinaryPredicateOperator(predicate.getBinaryType(), s1, n);
        } else if (s1.isConstant() && s2.isVariable()) {
            String fnName = RIGHT_COMMUTATIVE_MAP.get(call.getFunction().getFunctionName().toString());
            Function fn = findArithmeticFunction(call, fnName);

            if (fnName.equalsIgnoreCase(call.getFunction().getFunctionName().toString())) {
                CallOperator n = new CallOperator(fnName, call.getType(), Lists.newArrayList(s1, result), fn);
                return new BinaryPredicateOperator(predicate.getBinaryType(), n, s2);
            } else {
                CallOperator n = new CallOperator(fnName, call.getType(), Lists.newArrayList(result, s1), fn);
                return new BinaryPredicateOperator(predicate.getBinaryType(), s2, n);
            }
        }

        return predicate;
    }

    private Function findArithmeticFunction(CallOperator call, String fnName) {
        return Expr.getBuiltinFunction(fnName, call.getFunction().getArgs(), Function.CompareMode.IS_IDENTICAL);
    }
}
