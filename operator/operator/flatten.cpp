/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: chunyinglv@openailab.com
 */
#include "operator/flatten.hpp"

namespace TEngine {

bool Flatten::InferShape(const std::vector<TEngine::TShape>& ishape, std::vector<TEngine::TShape>& oshape, int layout)
{
    const TShape& input = ishape[0];

    const std::vector<int>& in_dim = input.GetDim();
    int in_size = in_dim.size();

    int new_channel = 1;
    for (int i = param_.axis; i <= param_.end_axis && i < in_size; i++)
    {
        new_channel *= in_dim[i];
    }

    TShape shape;
    std::vector<int> dim = {in_dim[0], new_channel, 1, 1};
    shape.SetDim(dim);
    shape.SetDataLayout(input.GetDataLayout());
    oshape[0] = shape;
    return true;
}

void Flatten::SetSchema(void)
{
    Input({"input:float32"})
        .Output({"output:float32"})
        .SetAttr("axis", 1)
        .SetAttr("end_axis", 3)
        .SetDoc(R"DOC(Flatten Layer)DOC");
}

}    // namespace TEngine
