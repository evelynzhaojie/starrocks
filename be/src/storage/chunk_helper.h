// This file is licensed under the Elastic License 2.0. Copyright 2021-present, StarRocks Inc.

#pragma once

#include <memory>
#include <queue>

#include "column/vectorized_fwd.h"
#include "storage/olap_common.h"
#include "storage/olap_type_infra.h"

namespace starrocks {

class Status;
class TabletColumn;
class TabletSchema;
class SlotDescriptor;
class TupleDescriptor;

class ChunkHelper {
public:
    static vectorized::VectorizedField convert_field(ColumnId id, const TabletColumn& c);

    static vectorized::VectorizedSchema convert_schema(const TabletSchema& schema);

    // Convert TabletColumn to vectorized::VectorizedField. This function will generate format
    // V2 type: DATE_V2, TIMESTAMP, DECIMAL_V2
    static vectorized::VectorizedField convert_field_to_format_v2(ColumnId id, const TabletColumn& c);

    // Convert TabletSchema to vectorized::VectorizedSchema with changing format v1 type to format v2 type.
    static vectorized::VectorizedSchema convert_schema_to_format_v2(const TabletSchema& schema);

    // Convert TabletSchema to vectorized::VectorizedSchema with changing format v1 type to format v2 type.
    static vectorized::VectorizedSchema convert_schema_to_format_v2(const TabletSchema& schema,
                                                                    const std::vector<ColumnId>& cids);

    // Get schema with format v2 type containing short key columns from TabletSchema.
    static vectorized::VectorizedSchema get_short_key_schema_with_format_v2(const TabletSchema& tablet_schema);

    static ColumnId max_column_id(const vectorized::VectorizedSchema& schema);

    // Create an empty chunk according to the |schema| and reserve it of size |n|.
    static std::shared_ptr<vectorized::Chunk> new_chunk(const vectorized::VectorizedSchema& schema, size_t n);

    // Create an empty chunk according to the |tuple_desc| and reserve it of size |n|.
    static std::shared_ptr<vectorized::Chunk> new_chunk(const TupleDescriptor& tuple_desc, size_t n);

    // Create an empty chunk according to the |slots| and reserve it of size |n|.
    static std::shared_ptr<vectorized::Chunk> new_chunk(const std::vector<SlotDescriptor*>& slots, size_t n);

    static vectorized::Chunk* new_chunk_pooled(const vectorized::VectorizedSchema& schema, size_t n, bool force = true);

    // Create a vectorized column from field .
    // REQUIRE: |type| must be scalar type.
    static std::shared_ptr<vectorized::Column> column_from_field_type(LogicalType type, bool nullable);

    // Create a vectorized column from field.
    static std::shared_ptr<vectorized::Column> column_from_field(const vectorized::VectorizedField& field);

    // Get char column indexes
    static std::vector<size_t> get_char_field_indexes(const vectorized::VectorizedSchema& schema);

    // Padding char columns
    static void padding_char_columns(const std::vector<size_t>& char_column_indexes,
                                     const vectorized::VectorizedSchema& schema, const TabletSchema& tschema,
                                     vectorized::Chunk* chunk);

    // Reorder columns of `chunk` according to the order of |tuple_desc|.
    static void reorder_chunk(const TupleDescriptor& tuple_desc, vectorized::Chunk* chunk);
    // Reorder columns of `chunk` according to the order of |slots|.
    static void reorder_chunk(const std::vector<SlotDescriptor*>& slots, vectorized::Chunk* chunk);

    // Convert a filter to select vector
    static void build_selective(const std::vector<uint8_t>& filter, std::vector<uint32_t>& selective);
};

// Accumulate small chunk into desired size
class ChunkAccumulator {
public:
    ChunkAccumulator() = default;
    ChunkAccumulator(size_t desired_size);
    void set_desired_size(size_t desired_size);
    void reset();
    Status push(vectorized::ChunkPtr&& chunk);
    void finalize();
    bool empty() const;
    vectorized::ChunkPtr pull();

private:
    size_t _desired_size;
    vectorized::ChunkPtr _tmp_chunk;
    std::deque<vectorized::ChunkPtr> _output;
};

class ChunkPipelineAccumulator {
public:
    ChunkPipelineAccumulator() = default;
    void set_max_size(size_t max_size) { _max_size = max_size; }
    void push(const vectorized::ChunkPtr& chunk);
    vectorized::ChunkPtr& pull();
    void finalize();
    void reset();

    bool has_output() const;
    bool need_input() const;
    bool is_finished() const;

private:
    static constexpr double LOW_WATERMARK_ROWS_RATE = 0.75;          // 0.75 * chunk_size
    static constexpr size_t LOW_WATERMARK_BYTES = 256 * 1024 * 1024; // 256MB.
    vectorized::ChunkPtr _in_chunk = nullptr;
    vectorized::ChunkPtr _out_chunk = nullptr;
    size_t _max_size = 4096;
    bool _finalized = false;
};

} // namespace starrocks
