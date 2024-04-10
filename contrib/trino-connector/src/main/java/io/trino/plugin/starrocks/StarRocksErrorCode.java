// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package io.trino.plugin.starrocks;

import io.trino.spi.ErrorCode;
import io.trino.spi.ErrorCodeSupplier;
import io.trino.spi.ErrorType;

import static io.trino.spi.ErrorType.EXTERNAL;

public enum StarRocksErrorCode implements ErrorCodeSupplier
{
    STAR_ROCKS_WRITE_ERROR(0, EXTERNAL)
    /**/;

    private final ErrorCode errorCode;

    StarRocksErrorCode(int code, ErrorType type)
    {
        errorCode = new ErrorCode(code + 0x0102_0000, name(), type);
    }

    @Override
    public ErrorCode toErrorCode()
    {
        return errorCode;
    }
}
