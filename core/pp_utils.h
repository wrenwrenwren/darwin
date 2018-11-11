// Copyright 2018 The Darwin Neuroevolution Framework Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <atomic>

namespace pp {

template <class T>
void atomicMax(std::atomic<T>& max, T value) {
  T prev = max;
  while (value > prev && !max.compare_exchange_weak(prev, value))
    ;
}

template <class T>
void atomicMin(std::atomic<T>& min, T value) {
  T prev = min;
  while (value < prev && !min.compare_exchange_weak(prev, value))
    ;
}

} // namespace pp
