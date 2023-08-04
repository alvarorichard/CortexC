#pragma once

#ifdef __cplusplus
extern "C" {
#endif
int function_parameter();
void function_body();

#if defined(__linux__) || defined(__APPLE__)
void setup_debug_handlers();
#endif

#ifdef __cplusplus
}
#endif