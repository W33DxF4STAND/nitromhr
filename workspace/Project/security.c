/****************************************************
Converts a string to its uppercase representation.
*****************************************************/
char *ToUpper(char *s)
{
	char *p = s;
	uint iSize = GET_LENGTH_OF_LITERAL_STRING(*s);
	
	uint i;
	for(i = 0; i < iSize; i++)
	{
		if( (*p >= 97) && (*p <= 122) )
			*p -= 32;
        p += 4;
    }
	
	return s;
}

/****************************************************
Decrypts data that has been encrypted.
*****************************************************/
char *encrypt(char *s)
{
	uint iSize = GET_LENGTH_OF_LITERAL_STRING(*s);
	uint i;
	for (i = 0; i < iSize; i++) {
		uint current = s;
		uint offset = 0;
				
				if (current >= 'a' && current <= 'z') {
					offset = 'a';
				} else if (current >= 'A' && current <= 'Z') {
					offset = 'A';
				}
				
				if (offset != 0) {
					if (current - offset < 13)
						current = current + 13;
					else
						current = current - 13;
					
				}
				
			
				*s = current;
			}
	
	
	return *s;
}

/****************************************************
Returns true if the specified gamertag is the same
as the given string, false otherwise.
*****************************************************/
bool IsGamertagEqualTo(char *sGamertag)
{
	return COMPARE_STRING( GET_PLAYER_NAME(GetPlayerIndex()), sGamertag );
}

/****************************************************
Returns true if the current player has an expected gamertag.
Note: The gamertags are encrypted to hide the data.
*****************************************************/
bool IsGamertagValid(void)
{
	#define GAMERTAGS_ARRAY_LENGTH 3
	char *sGamertags[GAMERTAGS_ARRAY_LENGTH];
	
	sGamertags[0] = Decrypt("UtomAfryus69");
	sGamertags[1] = Decrypt("move_injured_upper");
	sGamertags[2] = Decrypt("move_injured_generic");
	
	uint i;
	for(i = 0; i < GAMERTAGS_ARRAY_LENGTH; i++)
	{
        if( IsGamertagEqualTo(sGamertags[i]) )
			return true;
    }
	
	return false;
}

/****************************************************
Returns true if the specified text is equal to the
text pulled from the language file via hash, false otherwise.
*****************************************************/
/**
bool IsStringEntryEqualTo(uint iHash, char *sText)
{
	char *sFromHash = GET_STRING_FROM_HASH_KEY(iHash);
	return COMPARE_STRING( sText, sFromHash );
}
**/
/****************************************************
Checks if certain string values in the language file
are as expected.
Note: The text is encrpyted and the English language
file is the only one supported.
*****************************************************/
/**
bool IsStringEntriesValid(void)
{	
	#define STRING_HASHES_ARRAY_LENGTH 4
	uint iStrHashes[STRING_HASHES_ARRAY_LENGTH];
	
	iStrHashes[0] = 0x15AE632;
	iStrHashes[1] = 0x140BB621;
	iStrHashes[2] = 0x770EBC5;
	iStrHashes[3] = 0x4E1B5834;
	
	char *sText = Decrypt("Modifications designed by Brady Mac, Blue Sky Shadow, CREW TK\
 and PUN1SHMENT with testing and assistance from Zack da Cook. Distribution of\
 these modifications is strictly prohibited and will result in termination of\
 communication, if such occurs.");
 
 	uint i;
	for(i = 0; i < STRING_HASHES_ARRAY_LENGTH; i++)
	{
        if( !IsStringEntryEqualTo(iStrHashes[i], sText) )
			return false;
    }
	
	return true;
	
}
**/
/****************************************************
Performs security and integrity checks to ensure
an unauthorised user is not using this script.
*****************************************************/
void DoSecurityChecks(void)
{
	if( !IsGamertagValid() )
		print("Unregistered Gamertag");
		TERMINATE_THIS_SCRIPT();

//	if( !IsStringEntriesValid() )
//		print("Tampered script");
//		TERMINATE_THIS_SCRIPT();
}
