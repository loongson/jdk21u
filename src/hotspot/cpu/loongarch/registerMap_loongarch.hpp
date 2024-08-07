/*
 * Copyright (c) 1998, 2010, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2015, 2023, Loongson Technology. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef CPU_LOONGARCH_REGISTERMAP_LOONGARCH_HPP
#define CPU_LOONGARCH_REGISTERMAP_LOONGARCH_HPP

// machine-dependent implementation for register maps
  friend class frame;

 private:
  // This is the hook for finding a register in an "well-known" location,
  // such as a register block of a predetermined format.
  // Since there is none, we just return null.
  // See registerMap_sparc.hpp for an example of grabbing registers
  // from register save areas of a standard layout.
  address pd_location(VMReg reg) const {return nullptr;}
  address pd_location(VMReg base_reg, int slot_idx) const {
    if (base_reg->is_FloatRegister()) {
      assert(base_reg->is_concrete(), "must pass base reg");
      intptr_t offset_in_bytes = slot_idx * VMRegImpl::stack_slot_size;
      address base_location = location(base_reg, nullptr);
      if (base_location != nullptr) {
        return base_location + offset_in_bytes;
      } else {
        return nullptr;
      }
    } else {
      return location(base_reg->next(slot_idx), nullptr);
    }
  }

  // no PD state to clear or copy:
  void pd_clear() {}
  void pd_initialize() {}
  void pd_initialize_from(const RegisterMap* map) {}

#endif // CPU_LOONGARCH_REGISTERMAP_LOONGARCH_HPP
