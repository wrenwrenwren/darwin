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

#include "utils.h"

#include <functional>
#include <map>
#include <memory>
#include <string>
using namespace std;

namespace core {

//! A set of instances implementing common interface
//! (primarily intended to support registering named factory objects)
template <class INTERFACE>
class ImplementationsSet : public core::NonCopyable {
 public:
  //! Registers a concrete implementation
  template <class FACTORY>
  void add(const string& name) {
    CHECK(factories_.insert({ name, make_unique<FACTORY>() }).second);
  }

  //! Returns a previously registered instance
  //! (or nullptr if the name doesn't map to a registered instance)
  INTERFACE* find(const string& name) const {
    auto it = factories_.find(name);
    return it != factories_.end() ? it->second.get() : nullptr;
  }

  //! Registered instances begin iterator
  auto begin() const { return factories_.begin(); }

  //! Registered instances end iterator
  auto end() const { return factories_.end(); }

  //! Returns true if the set of registered instances is empty
  bool empty() const { return factories_.empty(); }

 private:
  map<string, unique_ptr<INTERFACE>> factories_;
};

}  // namespace core
