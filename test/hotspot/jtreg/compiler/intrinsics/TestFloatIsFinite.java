/*
 * Copyright (c) 2022, BELLSOFT. All rights reserved.
 * Copyright (c) 2022, Oracle and/or its affiliates. All rights reserved.
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
 */

/*
 * This file has been modified by Loongson Technology in 2022. These
 * modifications are Copyright (c) 2022, Loongson Technology, and are made
 * available on the same license terms set forth above.
 */

/**
* @test
* @summary Test intrinsics for Float.isFinite.
* @requires os.arch == "riscv64" | os.arch == "loongarch64"
* @library /test/lib /
* @run driver compiler.intrinsics.TestFloatIsFinite
*/

package compiler.intrinsics;
import compiler.lib.ir_framework.*;

public class TestFloatIsFinite extends TestFloatClassCheck {
    public static void main(String args[]) {
        TestFramework.run(TestFloatIsFinite.class);
    }

    @Test // needs to be run in (fast) debug mode
    @Warmup(10000)
    @IR(counts = {IRNode.IS_FINITE_F, ">= 1"}) // At least one IsFiniteF node is generated if intrinsic is used
    public void testIsFinite() {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            outputs[i] = Float.isFinite(inputs[i]);
        }
        checkResult("isFinite");
    }
}
