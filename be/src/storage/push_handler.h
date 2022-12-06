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

#include <vector>

#include "exec/vectorized/file_scanner.h"
#include "runtime/descriptors.h"
#include "storage/olap_common.h"
#include "storage/push_utils.h"
#include "storage/rowset/rowset.h"
#include "storage/tablet.h"

namespace starrocks::vectorized {

struct TabletVars {
    TabletSharedPtr tablet;
    RowsetSharedPtr rowset_to_add;
};

// Vectorized push handler for spark load.
// The parquet files generated by spark dpp are divided by tablet and the data is sorted,
// so the push handler reads the parquet file through the broker and directly writes the rowset.
class PushHandler {
public:
    PushHandler() = default;
    ~PushHandler() = default;

    // Load local data file into specified tablet.
    Status process_streaming_ingestion(const TabletSharedPtr& tablet, const TPushReq& request, PushType push_type,
                                       std::vector<TTabletInfo>* tablet_info_vec);

    int64_t write_bytes() const { return _write_bytes; }
    int64_t write_rows() const { return _write_rows; }

private:
    Status _do_streaming_ingestion(TabletSharedPtr tablet, const TPushReq& request, PushType push_type,
                                   vector<TabletVars>* tablet_vars, std::vector<TTabletInfo>* tablet_info_vec);

    void _get_tablet_infos(const std::vector<TabletVars>& tablet_infos, std::vector<TTabletInfo>* tablet_info_vec);

    Status _load_convert(const TabletSharedPtr& cur_tablet, RowsetSharedPtr* cur_rowset);
    Status _delete_convert(const TabletSharedPtr& cur_tablet, RowsetSharedPtr* cur_rowset);

private:
    // mainly tablet_id, version and delta file path
    TPushReq _request;

    int64_t _write_bytes = 0;
    int64_t _write_rows = 0;
};
} // namespace starrocks::vectorized
