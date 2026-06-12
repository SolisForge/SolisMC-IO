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
def list_to_bytes(values: list, fmt: str) -> bytes:
    b = b""
    for value in values:
        b += value_to_bytes(value, fmt)
    return b

# =============================================================================
def value_to_bytes(v: int, fmt: str) -> bytes:
    return struct.pack(f">{fmt}", v)

# =============================================================================
def byte_to_array(b_t: bytes) -> str:
    return ','.join([f"\'\\x{b:>02x}\'" for b in b_t])

