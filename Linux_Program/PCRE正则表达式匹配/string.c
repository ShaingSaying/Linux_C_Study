#include "mstring.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef BM_DEBUG
static int max_memory = 0;
#endif

/***********************************
 * bad character array
 **********************************/
int *make_skip(char *ptrn, int plen)
{
    int  i;
    int *skip = (int *) calloc(1, ALPHABET_SIZE * sizeof(int));
    if(skip == NULL)
    {
        return NULL;
    }

#ifdef BM_DEBUG
    max_memory += ALPHABET_SIZE * sizeof(int);
#endif

    for ( i = 0; i < ALPHABET_SIZE; i++ )
        skip[i] = plen + 1;

    while(plen != 0)
        skip[(unsigned char) *ptrn++] = plen--;

    return skip;
}


/****************************************
 *good suffix array
 ***************************************/
int *make_shift(char *ptrn, int plen)
{
    int *shift = (int *) calloc(1, plen * sizeof(int));
    if(shift == NULL)
    {
        return NULL;
    }

#ifdef BM_DEBUG
    max_memory += plen * sizeof(int);
#endif
    
    int *sptr = shift + plen - 1;
    char *pptr = ptrn + plen - 1;
    char c;

     c = ptrn[plen - 1];

    *sptr = 1;

    while(sptr-- != shift)
    {
        char *p1 = ptrn + plen - 2, *p2, *p3;

        do
        {
            while(p1 >= ptrn && *p1-- != c);

            p2 = ptrn + plen - 2;
            p3 = p1;

            while(p3 >= ptrn && *p3-- == *p2-- && p2 >= pptr);
        }
        while(p3 >= ptrn && p2 >= pptr);

        *sptr = shift + plen - sptr + p2 - p3;

        pptr--;
    }

    return shift;
}
/***************************************************************************************
 *string match
 ***************************************************************************************/
int bmSearch(const char *buf, int blen, const char *ptrn, int plen, int *skip, int *shift)
{
    int b_idx = plen;

    if(plen == 0)
        return 1;

    while(b_idx <= blen)
    {
        int p_idx = plen, skip_stride, shift_stride;

        while(buf[--b_idx] == ptrn[--p_idx])
        {
            if(b_idx < 0)
                return 0;

            if(p_idx == 0)
            {
                return 1;
            }
        }

        skip_stride = skip[(unsigned char) buf[b_idx]];
        shift_stride = shift[p_idx];

        b_idx += (skip_stride > shift_stride) ? skip_stride : shift_stride;
    }

    return 0;
}

int* make_skip_sunday(char * ptrn, int plen)
{
    int i = 0;
    int* skip = (int *) calloc(1, ALPHABET_SIZE * sizeof(int));
	if(skip == NULL)
    {
        return NULL;
    }

#ifdef SUNDAY_DEBUG
    max_memory += ALPHABET_SIZE * sizeof(int);
#endif

	for(i = 0; i<ALPHABET_SIZE; i++)
		skip[i] = -1;
	for(i = 0; i<plen; i++)
		skip[ptrn[i]] = i;

	return skip;
}

int sunday_search(const char * buf, int blen, const char * ptrn, int plen, int * skip)
{	
    int i = 0, j = 0, k = 0;

	if (blen == 0)
	{
		return 0;
	}

	for (i = 0; i <= blen - plen;)
	{
		j = i;
		k = 0;

		for (; k < plen && j < blen && (buf[j] == ptrn[k]); j++, k++)
	    {
			;//do nothing
	    }

		if (k == plen)
		{
		    /* great! find it! */
			return 1;
		}
		else
		{
			if (i + plen < blen)
			{
				i += (plen - skip[(buf[i + plen])]);
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

void clear_state()
{

#ifdef SUNDAY_DEBUG
    max_memory = 0;
#endif

#ifdef BM_DEBUG
    max_memory = 0;
#endif
}

void print_bm_res_usage()
{
    LOG_INFO("+--[BM algorithm]----------------------------\n");
#ifdef SUNDAY_DEBUG
    if( max_memory < 1024*1024 )
    {
        LOG_INFO("| Memory           : %.2fKbytes\n", (float)max_memory/1024 );
    }
    else
    {
        LOG_INFO("| Memory           : %.2fMbytes\n", (float)max_memory/(1024*1024) );
    }
#endif
    LOG_INFO("+-------------------------------------------------------------\n");
}

void print_sunday_res_usage()
{
    LOG_INFO("+--[sunday algorithm]----------------------------\n");
#ifdef SUNDAY_DEBUG
    if( max_memory < 1024*1024 )
    {
        LOG_INFO("| Memory           : %.2fKbytes\n", (float)max_memory/1024 );
    }
    else
    {
        LOG_INFO("| Memory           : %.2fMbytes\n", (float)max_memory/(1024*1024) );
    }
#endif
    LOG_INFO("+-------------------------------------------------------------\n");
}


/* implement regular match below */
pcre* compile_regex(char* pattern)
{
    const char* errptr = NULL;
    int   erroffset = 0;

    pcre* re = NULL;
	/* 正则匹配时忽略大小写 */
    if((re = pcre_compile(pattern, PCRE_CASELESS, &errptr, &erroffset, NULL)) == NULL)
    {
        LOG_INFO("compile regular expression failed at %s, %d\n", errptr, erroffset);
    }

    return re;
}

int match_regex_from(pcre* re, pcre_extra* extra, char* buf, int len, int option, int offset)
{
    int ovector[overcount] = {0};
    
    return pcre_exec(re, extra, buf, len, offset, option, ovector, overcount);
}

int match_regex(pcre* re, pcre_extra* extra, char* buf, int len)
{
    return match_regex_from(re, extra, buf, len, 0, 0);
}

void free_regex(void* re)
{
    pcre_free((pcre*)re);
}

void free_regex_extra(void* extra)
{
    pcre_free_study((pcre_extra*)extra);
}

pcre_extra* create_pcre_study(pcre* re)
{
    const char* errptr = NULL;
	pcre_extra* extra = NULL;
	if((extra = pcre_study(re, PCRE_STUDY_JIT_COMPILE, &errptr)) == NULL)
	{
	    return NULL;
	}
	return extra;
}



/* 消除字符串的行尾换行符 */
int erase_lineend_lf(char* strs)
{
    int len = 0;
    if(strs == NULL || strs[0] == '\0')
    {
        /* 空或空串 */
        return -1;
    }

	len = strlen(strs);
    if(strs[len - 2] == '\r' && strs[len - 1] == '\n')
    {
        strs[len - 2] = '\0';
		len -= 2;
    }
    else if(strs[len - 1] == '\n')
    {
        strs[len - 1] = '\0';
		len -= 1;
    }
	else
	{
	    ;  /* pass */
	}

	return len;
}

/**********************************************************************
* 函 数 名 : convert_str
* 功能描述 : 字符串转化，将所有与sql语法规范的字符全部用
* 输入参数 : char* dest:
*            const char* str:
*			 int len:
* 输出参数 :  
*
* 返 回 值 : int
* 
* 修改历史 :
* 日     期 : 2018年9月6日
* 作     者 : lbh
* 修改内容 : 
* 
**********************************************************************/
char* convert_str(char* dest, const char* str, int len)
{
    int i, j = 0;

    for(i = 0; i < len; i++)
    {
        if(str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
        {
            dest[j++] = '\\';
            dest[j++] = str[i];
        }
        else
        {
            dest[j++] = str[i];
        }
    }

	dest[j] = 0;
	return dest;
}

/**********************************************************************
* 函 数 名 : string_cmp
* 功能描述 : 排序的比较函数
* 输入参数 : const void* lval:
*            const void* rval:
* 输出参数 :  
*
* 返 回 值 : int
* 
* 修改历史 :
* 日     期 : 2018年9月6日
* 作     者 : lbh
* 修改内容 : 
* 
**********************************************************************/
int string_cmp(const void* lval, const void* rval)
{
    int ret;
    match_rules* v1 = (match_rules*)lval;
	match_rules* v2 = (match_rules*)rval;

	/* 先按uuid比较，uuid相同的按key_field比较 */
	ret = strcmp(v1->rule_uuid, v2->rule_uuid);
	if(ret)
	{
	    return ret;
	}
	else
	{
	    return strcmp(v1->key_field, v2->key_field);
	}
}

/* 字符串分割 */
void split_strings(char* strings, const char* delm, char (*dest)[UUIDLEN], int* cnt)
{
    /* 该函数非线程安全，且最多只能切分MAXSETNUM个uuid */
    int index;
    char* tok;
	static char strings_cpy[UUIDLEN * MAXSETNUM + MAXSETNUM];
	
	index = 0;
    if(strings == NULL || strings[0] == '\0')
    {
        return;
    }
	snprintf(strings_cpy, MAXSETNUM * (UUIDLEN + 1), "%s", strings);
	tok = strtok(strings_cpy, delm);
	while(tok != NULL && index <= MAXSETNUM)
	{
	    snprintf(dest[index++], UUIDLEN, "%s", tok);
		tok = strtok(NULL, delm);
	}
	*cnt = index;
}

void split_strings_100(char* strings, const char* delm, char (*dest)[STRINGELEM], int* cnt)
{
    /* 该函数非线程安全，且最多只能切分MAXSETNUM个字符串元素 */
    int index;
    char* tok;
	static char strings_cpy[STRINGELEM * MAXSETNUM + MAXSETNUM];
	
	index = 0;
    if(strings == NULL || strings[0] == '\0')
    {
        return;
    }
	snprintf(strings_cpy, MAXSETNUM * (STRINGELEM + 1), "%s", strings);
	tok = strtok(strings_cpy, delm);
	while(tok != NULL && index <= MAXSETNUM)
	{
	    snprintf(dest[index++], STRINGELEM, "%s", tok);
		tok = strtok(NULL, delm);
	}
	*cnt = index;
}


char* strtok_str(char* str, const char* delm)
{
    /* 以字符串delm切分字符串str */
    char* end_ptr;
	char* mid, *ret;
	static char* save_ptr = NULL;

	if(str)
	{
	    mid = strstr(str, delm);
		if(mid)
		{
		    save_ptr = mid + strlen(delm);
		}
		else
		{
		    save_ptr = str + strlen(str);
		}
		if(mid)
		{
		    *mid = '\0';
		}
		return str;
	}
	else
	{
	    end_ptr = save_ptr + strlen(save_ptr);
		if(save_ptr >= end_ptr)
		{
		    save_ptr = NULL;
			return NULL;
		}
		mid = strstr(save_ptr, delm);
		if(mid == NULL)
		{
		    ret = save_ptr;
			save_ptr = save_ptr + strlen(save_ptr);
			return ret;
		}
		ret = save_ptr;
		save_ptr = mid + strlen(delm);
		*mid = '\0';
		return ret;
	}
}

char* strip(char* str)
{
    /* 消除字符串前面和后面的空格 */
    int len;
	char* end_ptr, *ret;
	if(str == NULL || str[0] == '\0')
	{
	    return str;
	}
	ret = str;
	len = strlen(str);
	end_ptr = str + len;

	while(str < end_ptr && isspace(*str))
	{
	    str++;
	}
	if(str == end_ptr)
	{
	    ret[0] = '\0';
		return ret;
	}
	end_ptr = end_ptr - 1;
	while(end_ptr >= ret && isspace(*end_ptr))
	{
	    *end_ptr = '\0';
		end_ptr -= 1;
	}
	return str;
}



