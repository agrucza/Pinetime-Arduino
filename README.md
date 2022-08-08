<!--
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
-->

# Pinetime-newt

## Overview

This project is an attempt to create a Pinetime firmware based on Apache mynewt. I have created this project inside of Visual Studio Code and its configured to have the build and debug process included as VSCode tasks and launch configs to make this easy as possible.

## Building

The mynetw pinetime BSP scripts are set to use the famous ST-Link V2 for uploading and debugging. I use a [Segger J-Link EDU Mini](https://www.segger.com/products/debug-probes/j-link/models/j-link-edu-mini/) for SWD uploads and debugging so the debugger setup is based on the J-Link interface. If you use a ST-Link V2 you need to create your own debugger `.vscode/launch.json` file for this.

1. Download and install Apache Newt.

You will need to download the Apache Newt tool, as documented in the [mynewt.apache.org Getting Started Guide](https://mynewt.apache.org/latest/get_started/index.html).

2. Download the Apache Mynewt Core package (executed from the project directory).

```no-highlight
    $ newt install
```

If you want to use the J-Link for uploading and debugingyou need to adjust two files after zou installed the mynewt core package:

`repos/apache-mynewt-core/hw/bsp/pinetime/pinetime_download.sh`

```no-highlight
. $CORE_PATH/hw/scripts/jlink.sh
cfg -f target/nrf52.cfg"
if [ "$MFG_IMAGE" ]; then
    FLASH_OFFSET=0
fi
JLINK_DEV="NRF52832_XXAA"
common_file_to_load
jlink_load
```

Please review any nrf52 bsp as reference. This is what i did and it worked out so far.

`repos/apache-mynewt-core/hw/bsp/pinetime/pinetime_debug.sh`
```no-highlight
. $CORE_PATH/hw/scripts/jlink.sh
FILE_NAME=$BIN_BASENAME.elf
if [ $# -gt 2 ]; then
    SPLIT_ELF_NAME=$3.elf
    EXTRA_GDB_CMDS="add-symbol-file $SPLIT_ELF_NAME 0x8000 -readnow"
fi
JLINK_DEV="nRF52"
jlink_debug
```

3. Please use `Ctrl+Shift+P` to open the VSCode command console and select `Tasks: Run Task` to access the individual build and upload tasks:

```no-highlight
    Build Pinetime Boot
```

Build the bootloader

```no-highlight
    Upload Pinetime Boot
```

Upload the bootloader to the Pinetime

```no-highlight
    Build Pinetime
```

Build the Pinetime firmware

```no-highlight
    Create Pinetime
```

Create the Pinetime firmware img file

```no-highlight
    Upload Pinetime
```

Upload the firmware img to the Pinetime

## Debugging

```no-highlight
    Debug Pinetime
```

Will open a debug server using the J-Link interface. Using the VSCode extension [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) you will be able to connect directly to the debug server opened by the task. Just select `Debug J-Link` and start the debug session.
