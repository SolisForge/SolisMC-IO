# =============================================================================
# Project: SOLISMC-IO
#
# Byte conversion functions for dataset
#
# Author    Meltwin (github@meltwin.fr)
# Date      02/06/2026 (created 02/06/2026)
# Version   1.0.0
# Copyright Solis Forge | 2026
#           Distributed under MIT License (https://opensource.org/licenses/MIT)
# =============================================================================
import struct

# =============================================================================
def int_to_bytes(v: int, fmt: str) -> bytes:
    return struct.pack(f">{fmt}", v)
