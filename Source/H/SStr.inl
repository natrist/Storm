#ifndef __SSTR_INL__
#define __SSTR_INL__

inline int ToLower(int ch);

inline int ToUpper(int ch);

inline int IsDigit(int ch);

inline char *SStrToLower(char *string);

inline char *SStrToUpper(char *string);

inline char *SStrCopy(char *dest, const char *source);

inline char *SStrNumCopy(char *dest, const char *source, unsigned int maxchar);

inline unsigned int SStrLength(const char *str);

inline char *SStrChr(char *string, int ch);

inline const char *SStrChr(const char *string, int ch);

inline void SStrTokenize(const char **string, char *buffer, unsigned int maxbufchars, const char *whitespace);

#endif
