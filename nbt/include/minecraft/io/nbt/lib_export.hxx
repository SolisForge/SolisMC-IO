// ============================================================================
// Project: SOLISMC_IO
//
// Library object exports
//
// Author    meltwin
// Created   23/10/2026
// ============================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

// ============================================================================
// Windows EXPORT
// ============================================================================
#if defined(_WIN32) || defined(__CYGWIN__)
// Windows EXPORT
#ifdef LIBNBT_EXPORTS
#define NBT_EXPORT __declspec(dllexport)
#else
#define NBT_EXPORT __declspec(dllimport)
#endif

// ============================================================================
// LINUX EXPORT
// ============================================================================
#else
#if __GNUC__ >= 4
#define NBT_EXPORT __attribute__((visibility("default")))
#else
#define NBT_EXPORT
#endif

#endif
