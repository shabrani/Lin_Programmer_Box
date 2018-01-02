#include "stdafx.h"
#include "my_string.h"

#include <iostream>
#include <string>

#include "procedure_Macro.h"


using namespace std;


bool str_extract_token_with_BrokenChar (const char *s, char *token, unsigned bufsize, unsigned Nth, char broken_char)
{
	bool token_enable = false;			//token enable;	

	unsigned token_i     = 0;			//toekn index;
	unsigned token_count = 0;			//token index;	

	unsigned len = 0;					//string length
	unsigned i   = 0;					//string index;
	
	if (bufsize == 0) return false;

	len = strlen( s );
	if (len     == 0) 
	{
		token[token_i] = '\0';
		return false;
	}

	token_count++;
	if ( token_count == Nth ) token_enable = true;


	for(i=0; i < len; i++)
	{
		if (token_enable == true)
		{
			if ( s[i] == broken_char )
			{
				token[token_i] = '\0';
				return true;
			} 
			else 
			{
				if (token_i < (bufsize-1))
				{
					//buffer size이내면 저장함 
					token[token_i++] = s[i];
				}
				else 
				{
					//token bufsize가 작다면 NULL을 저장하고 false return 
					token[token_i] = '\0';
					return false;
				}
			}
		}
		else if (token_enable == false)  
		{
			if ( s[i] == broken_char )
			{
				//token_enable = true;
				token_count++;
				if (token_count == Nth) token_enable = true;
			}
		}
	}

	if (token_enable == true)
	{
		token[token_i] = '\0';
		return true;
	}

	return false;

}

unsigned str_count_token_with_BrokenChar(const char *s, char broken_char)
{
	unsigned token_count = 0;
	unsigned len;
	
	len = strlen( s );
	if ( len == 0) return 0;

	token_count ++;

	for (unsigned i=0; i<len; i++)
	{
		if ( s[i] == broken_char )
		{
			token_count++;
		}
	}

	return token_count;
}
