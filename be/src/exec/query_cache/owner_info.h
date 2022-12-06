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

#pragma once

#include <string>

namespace starrocks::query_cache {
// owner_info is attached to vectorized::Chunk to describe how chunk is generated.
// 1. owner_id: chunks originated from the same tablet should have the same owner_id
// 2. is_last_chunk returns true if the chunk is the last chunk.
// 3. is_passthrough returns true if the chunk is generated by pre-cache agg operators work in passthrough mode

class owner_info {
public:
    // |--last_chunk(1bit)--|--passthrough(1bit)|--owner_id(62bit)--|
    static constexpr int64_t LAST_CHUNK_BIT = 1L << 63;
    static constexpr int64_t PASSTHROUGH_BIT = 1L << 62;
    static constexpr int64_t LANE_OWNER_BITS = PASSTHROUGH_BIT - 1L;
    static constexpr int64_t LAST_CHUNK_MASK = ~LAST_CHUNK_BIT;
    static constexpr int64_t PASSTHROUGH_MASK = ~PASSTHROUGH_BIT;
    static constexpr int64_t LANE_OWNER_MASK = ~LANE_OWNER_BITS;

    void set_owner_id(int64_t owner_id, bool is_last_chunk) {
        _owner_id = owner_id | (is_last_chunk ? LAST_CHUNK_BIT : 0);
    }
    int64_t owner_id() const { return _owner_id & LANE_OWNER_BITS; }
    void set_last_chunk(bool on) { _owner_id = _owner_id | (on ? LAST_CHUNK_BIT : 0); }
    bool is_last_chunk() const { return (_owner_id & LAST_CHUNK_BIT) == LAST_CHUNK_BIT; }
    void set_passthrough(bool on) {
        if (on) {
            _owner_id = _owner_id | PASSTHROUGH_BIT;
        } else {
            _owner_id = _owner_id & PASSTHROUGH_MASK;
        }
    }
    bool is_passthrough() const { return (_owner_id & PASSTHROUGH_BIT) == PASSTHROUGH_BIT; }

private:
    int64_t _owner_id = 0;
};
} // namespace starrocks::query_cache
