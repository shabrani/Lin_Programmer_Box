#pragma once

#include <iostream>
#include <string>


unsigned str_count_token_with_BrokenChar	(const char *s, char broken_char);
bool     str_extract_token_with_BrokenChar	(const char *s, char *token, unsigned bufsize, unsigned Nth, char broken_char);
