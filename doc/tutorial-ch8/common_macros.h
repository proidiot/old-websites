#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/* 
 * Functions needed by all recursive macros
 */

#define MACRO_NUM_ARGS(...) \
	         _MACRO_NARG_(__VA_ARGS__,_MACRO_RSEQ_N())
#define _MACRO_NARG_(...) \
	         _MACRO_ARG_N(__VA_ARGS__)
#define _MACRO_ARG_N( \
		          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
		         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
		         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
		         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
		         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
		         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
		         _61,_62,_63,N,...) N
#define _MACRO_RSEQ_N() \
	         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define MACRO_CAT(a,b) a ## b

/*
 * COMMA_SEPARATED_STRING_LITERALS
 *
 * Adds a string literal comma between each of a series of string literals.
 *
 * Example: COMMA_SEPARATED_STRING_LITERALS("apple", "banana", "coconut")
 * Result:  "apple" ", " "banana" ", " "coconut"
 *
 */

#define COMMA_SEPARATED_STRING_LITERALS(...) _CSL_N(MACRO_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define _CSL_N(N,...) MACRO_CAT(_CSL_,N)(__VA_ARGS__)

#define _CSL_1(a) a
#define _CSL_2(a,b) a ", " b
#define _CSL_3(a,...) a ", " _CSL_2(__VA_ARGS__)
#define _CSL_4(a,...) a ", " _CSL_3(__VA_ARGS__)
#define _CSL_5(a,...) a ", " _CSL_4(__VA_ARGS__)
#define _CSL_6(a,...) a ", " _CSL_5(__VA_ARGS__)
#define _CSL_7(a,...) a ", " _CSL_6(__VA_ARGS__)
#define _CSL_8(a,...) a ", " _CSL_7(__VA_ARGS__)
#define _CSL_9(a,...) a ", " _CSL_8(__VA_ARGS__)
#define _CSL_10(a,...) a ", " _CSL_9(__VA_ARGS__)
#define _CSL_11(a,...) a ", " _CSL_10(__VA_ARGS__)
#define _CSL_12(a,...) a ", " _CSL_11(__VA_ARGS__)
#define _CSL_13(a,...) a ", " _CSL_12(__VA_ARGS__)
#define _CSL_14(a,...) a ", " _CSL_13(__VA_ARGS__)
#define _CSL_15(a,...) a ", " _CSL_14(__VA_ARGS__)
#define _CSL_16(a,...) a ", " _CSL_15(__VA_ARGS__)
#define _CSL_17(a,...) a ", " _CSL_16(__VA_ARGS__)
#define _CSL_18(a,...) a ", " _CSL_17(__VA_ARGS__)
#define _CSL_19(a,...) a ", " _CSL_18(__VA_ARGS__)
#define _CSL_20(a,...) a ", " _CSL_19(__VA_ARGS__)
#define _CSL_21(a,...) a ", " _CSL_20(__VA_ARGS__)
#define _CSL_22(a,...) a ", " _CSL_21(__VA_ARGS__)
#define _CSL_23(a,...) a ", " _CSL_22(__VA_ARGS__)
#define _CSL_24(a,...) a ", " _CSL_23(__VA_ARGS__)
#define _CSL_25(a,...) a ", " _CSL_24(__VA_ARGS__)
#define _CSL_26(a,...) a ", " _CSL_25(__VA_ARGS__)
#define _CSL_27(a,...) a ", " _CSL_26(__VA_ARGS__)
#define _CSL_28(a,...) a ", " _CSL_27(__VA_ARGS__)
#define _CSL_29(a,...) a ", " _CSL_28(__VA_ARGS__)
#define _CSL_30(a,...) a ", " _CSL_29(__VA_ARGS__)
#define _CSL_31(a,...) a ", " _CSL_30(__VA_ARGS__)
#define _CSL_32(a,...) a ", " _CSL_31(__VA_ARGS__)
#define _CSL_33(a,...) a ", " _CSL_32(__VA_ARGS__)
#define _CSL_34(a,...) a ", " _CSL_33(__VA_ARGS__)
#define _CSL_35(a,...) a ", " _CSL_34(__VA_ARGS__)
#define _CSL_36(a,...) a ", " _CSL_35(__VA_ARGS__)
#define _CSL_37(a,...) a ", " _CSL_36(__VA_ARGS__)
#define _CSL_38(a,...) a ", " _CSL_37(__VA_ARGS__)
#define _CSL_39(a,...) a ", " _CSL_38(__VA_ARGS__)
#define _CSL_40(a,...) a ", " _CSL_39(__VA_ARGS__)
#define _CSL_41(a,...) a ", " _CSL_40(__VA_ARGS__)
#define _CSL_42(a,...) a ", " _CSL_41(__VA_ARGS__)
#define _CSL_43(a,...) a ", " _CSL_42(__VA_ARGS__)
#define _CSL_44(a,...) a ", " _CSL_43(__VA_ARGS__)
#define _CSL_45(a,...) a ", " _CSL_44(__VA_ARGS__)
#define _CSL_46(a,...) a ", " _CSL_45(__VA_ARGS__)
#define _CSL_47(a,...) a ", " _CSL_46(__VA_ARGS__)
#define _CSL_48(a,...) a ", " _CSL_47(__VA_ARGS__)
#define _CSL_49(a,...) a ", " _CSL_48(__VA_ARGS__)
#define _CSL_50(a,...) a ", " _CSL_49(__VA_ARGS__)
#define _CSL_51(a,...) a ", " _CSL_50(__VA_ARGS__)
#define _CSL_52(a,...) a ", " _CSL_51(__VA_ARGS__)
#define _CSL_53(a,...) a ", " _CSL_52(__VA_ARGS__)
#define _CSL_54(a,...) a ", " _CSL_53(__VA_ARGS__)
#define _CSL_55(a,...) a ", " _CSL_54(__VA_ARGS__)
#define _CSL_56(a,...) a ", " _CSL_55(__VA_ARGS__)
#define _CSL_57(a,...) a ", " _CSL_56(__VA_ARGS__)
#define _CSL_58(a,...) a ", " _CSL_57(__VA_ARGS__)
#define _CSL_59(a,...) a ", " _CSL_58(__VA_ARGS__)
#define _CSL_60(a,...) a ", " _CSL_59(__VA_ARGS__)
#define _CSL_61(a,...) a ", " _CSL_60(__VA_ARGS__)
#define _CSL_62(a,...) a ", " _CSL_61(__VA_ARGS__)
#define _CSL_63(a,...) a ", " _CSL_62(__VA_ARGS__)


/*
 * SMATCH
 *
 * String match against a string literal.
 *
 * Example: SMATCH(method, "POST")
 * Result:  (strncmp((method), "POST", strlen("POST")+1))
 *
 */
#define SMATCH(s,l) (strncmp((s),""l"",strlen(""l"")+1)==0)

/*
 * SMATCH_ANY
 *
 * String match against any of a set of string literals.
 *
 * Example: SMATCH_ANY(method, "POST", "GET")
 * Result:  ((strncmp((method), "POST", strlen("POST")+1))
 * 		|| (strncmp((method), "GET", strlen("GET")+1)))
 *
 */

#define SMATCH_ANY(s,...) (_SMATCH_N(MACRO_NUM_ARGS(__VA_ARGS__),(s),__VA_ARGS__))
#define _SMATCH_N(N,s,...) MACRO_CAT(_SMATCH_,N)(s,__VA_ARGS__)

#define _SMATCH_1(s,a) SMATCH(s,a)
#define _SMATCH_2(s,a,b) SMATCH(s,a) || SMATCH(s,b)
#define _SMATCH_3(s,a,...) SMATCH(s,a) || _SMATCH_2(s,__VA_ARGS__)
#define _SMATCH_4(s,a,...) SMATCH(s,a) || _SMATCH_3(s,__VA_ARGS__)
#define _SMATCH_5(s,a,...) SMATCH(s,a) || _SMATCH_4(s,__VA_ARGS__)
#define _SMATCH_6(s,a,...) SMATCH(s,a) || _SMATCH_5(s,__VA_ARGS__)
#define _SMATCH_7(s,a,...) SMATCH(s,a) || _SMATCH_6(s,__VA_ARGS__)
#define _SMATCH_8(s,a,...) SMATCH(s,a) || _SMATCH_7(s,__VA_ARGS__)
#define _SMATCH_9(s,a,...) SMATCH(s,a) || _SMATCH_8(s,__VA_ARGS__)
#define _SMATCH_10(s,a,...) SMATCH(s,a) || _SMATCH_9(s,__VA_ARGS__)
#define _SMATCH_11(s,a,...) SMATCH(s,a) || _SMATCH_10(s,__VA_ARGS__)
#define _SMATCH_12(s,a,...) SMATCH(s,a) || _SMATCH_11(s,__VA_ARGS__)
#define _SMATCH_13(s,a,...) SMATCH(s,a) || _SMATCH_12(s,__VA_ARGS__)
#define _SMATCH_14(s,a,...) SMATCH(s,a) || _SMATCH_13(s,__VA_ARGS__)
#define _SMATCH_15(s,a,...) SMATCH(s,a) || _SMATCH_14(s,__VA_ARGS__)
#define _SMATCH_16(s,a,...) SMATCH(s,a) || _SMATCH_15(s,__VA_ARGS__)
#define _SMATCH_17(s,a,...) SMATCH(s,a) || _SMATCH_16(s,__VA_ARGS__)
#define _SMATCH_18(s,a,...) SMATCH(s,a) || _SMATCH_17(s,__VA_ARGS__)
#define _SMATCH_19(s,a,...) SMATCH(s,a) || _SMATCH_18(s,__VA_ARGS__)
#define _SMATCH_20(s,a,...) SMATCH(s,a) || _SMATCH_19(s,__VA_ARGS__)
#define _SMATCH_21(s,a,...) SMATCH(s,a) || _SMATCH_20(s,__VA_ARGS__)
#define _SMATCH_22(s,a,...) SMATCH(s,a) || _SMATCH_21(s,__VA_ARGS__)
#define _SMATCH_23(s,a,...) SMATCH(s,a) || _SMATCH_22(s,__VA_ARGS__)
#define _SMATCH_24(s,a,...) SMATCH(s,a) || _SMATCH_23(s,__VA_ARGS__)
#define _SMATCH_25(s,a,...) SMATCH(s,a) || _SMATCH_24(s,__VA_ARGS__)
#define _SMATCH_26(s,a,...) SMATCH(s,a) || _SMATCH_25(s,__VA_ARGS__)
#define _SMATCH_27(s,a,...) SMATCH(s,a) || _SMATCH_26(s,__VA_ARGS__)
#define _SMATCH_28(s,a,...) SMATCH(s,a) || _SMATCH_27(s,__VA_ARGS__)
#define _SMATCH_29(s,a,...) SMATCH(s,a) || _SMATCH_28(s,__VA_ARGS__)
#define _SMATCH_30(s,a,...) SMATCH(s,a) || _SMATCH_29(s,__VA_ARGS__)
#define _SMATCH_31(s,a,...) SMATCH(s,a) || _SMATCH_30(s,__VA_ARGS__)
#define _SMATCH_32(s,a,...) SMATCH(s,a) || _SMATCH_31(s,__VA_ARGS__)
#define _SMATCH_33(s,a,...) SMATCH(s,a) || _SMATCH_32(s,__VA_ARGS__)
#define _SMATCH_34(s,a,...) SMATCH(s,a) || _SMATCH_33(s,__VA_ARGS__)
#define _SMATCH_35(s,a,...) SMATCH(s,a) || _SMATCH_34(s,__VA_ARGS__)
#define _SMATCH_36(s,a,...) SMATCH(s,a) || _SMATCH_35(s,__VA_ARGS__)
#define _SMATCH_37(s,a,...) SMATCH(s,a) || _SMATCH_36(s,__VA_ARGS__)
#define _SMATCH_38(s,a,...) SMATCH(s,a) || _SMATCH_37(s,__VA_ARGS__)
#define _SMATCH_39(s,a,...) SMATCH(s,a) || _SMATCH_38(s,__VA_ARGS__)
#define _SMATCH_40(s,a,...) SMATCH(s,a) || _SMATCH_39(s,__VA_ARGS__)
#define _SMATCH_41(s,a,...) SMATCH(s,a) || _SMATCH_40(s,__VA_ARGS__)
#define _SMATCH_42(s,a,...) SMATCH(s,a) || _SMATCH_41(s,__VA_ARGS__)
#define _SMATCH_43(s,a,...) SMATCH(s,a) || _SMATCH_42(s,__VA_ARGS__)
#define _SMATCH_44(s,a,...) SMATCH(s,a) || _SMATCH_43(s,__VA_ARGS__)
#define _SMATCH_45(s,a,...) SMATCH(s,a) || _SMATCH_44(s,__VA_ARGS__)
#define _SMATCH_46(s,a,...) SMATCH(s,a) || _SMATCH_45(s,__VA_ARGS__)
#define _SMATCH_47(s,a,...) SMATCH(s,a) || _SMATCH_46(s,__VA_ARGS__)
#define _SMATCH_48(s,a,...) SMATCH(s,a) || _SMATCH_47(s,__VA_ARGS__)
#define _SMATCH_49(s,a,...) SMATCH(s,a) || _SMATCH_48(s,__VA_ARGS__)
#define _SMATCH_50(s,a,...) SMATCH(s,a) || _SMATCH_49(s,__VA_ARGS__)
#define _SMATCH_51(s,a,...) SMATCH(s,a) || _SMATCH_50(s,__VA_ARGS__)
#define _SMATCH_52(s,a,...) SMATCH(s,a) || _SMATCH_51(s,__VA_ARGS__)
#define _SMATCH_53(s,a,...) SMATCH(s,a) || _SMATCH_52(s,__VA_ARGS__)
#define _SMATCH_54(s,a,...) SMATCH(s,a) || _SMATCH_53(s,__VA_ARGS__)
#define _SMATCH_55(s,a,...) SMATCH(s,a) || _SMATCH_54(s,__VA_ARGS__)
#define _SMATCH_56(s,a,...) SMATCH(s,a) || _SMATCH_55(s,__VA_ARGS__)
#define _SMATCH_57(s,a,...) SMATCH(s,a) || _SMATCH_56(s,__VA_ARGS__)
#define _SMATCH_58(s,a,...) SMATCH(s,a) || _SMATCH_57(s,__VA_ARGS__)
#define _SMATCH_59(s,a,...) SMATCH(s,a) || _SMATCH_58(s,__VA_ARGS__)
#define _SMATCH_60(s,a,...) SMATCH(s,a) || _SMATCH_59(s,__VA_ARGS__)
#define _SMATCH_61(s,a,...) SMATCH(s,a) || _SMATCH_60(s,__VA_ARGS__)
#define _SMATCH_62(s,a,...) SMATCH(s,a) || _SMATCH_61(s,__VA_ARGS__)
#define _SMATCH_63(s,a,...) SMATCH(s,a) || _SMATCH_62(s,__VA_ARGS__)


/*
 * BOOL-related stuff
 */

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef FALSE
#define FALSE (0==1)
#endif


/*
 * NEWSTRING-related stuff
 */
#define NEWSTRING (char*)malloc(BUFSIZ)
#define SHRINKSTR(s) s = realloc((s), strnlen((s), BUFSIZ) + 1)
#define SHRINKSAFESTR(s) s = realloc((s), strlen((s)) + 1)

/*
 * MAX
 */
#define MAX(...) _MAX_N(MACRO_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define _MAX_N(N,...) MACRO_CAT(_MAX_,N)(__VA_ARGS__)

#define _MAX_1(a) (a)
#define _MAX_2(a,b) (((a)<(b))?(b):(a))
#define _MAX_3(a,...) (((a)<_MAX_2(__VA_ARGS__))?_MAX_2(__VA_ARGS__):(a))
#define _MAX_4(a,...) (((a)<_MAX_3(__VA_ARGS__))?_MAX_3(__VA_ARGS__):(a))
#define _MAX_5(a,...) (((a)<_MAX_4(__VA_ARGS__))?_MAX_4(__VA_ARGS__):(a))
#define _MAX_6(a,...) (((a)<_MAX_5(__VA_ARGS__))?_MAX_5(__VA_ARGS__):(a))
#define _MAX_7(a,...) (((a)<_MAX_6(__VA_ARGS__))?_MAX_6(__VA_ARGS__):(a))
#define _MAX_8(a,...) (((a)<_MAX_7(__VA_ARGS__))?_MAX_7(__VA_ARGS__):(a))
#define _MAX_9(a,...) (((a)<_MAX_8(__VA_ARGS__))?_MAX_8(__VA_ARGS__):(a))
#define _MAX_10(a,...) (((a)<_MAX_9(__VA_ARGS__))?_MAX_9(__VA_ARGS__):(a))
#define _MAX_11(a,...) (((a)<_MAX_10(__VA_ARGS__))?_MAX_10(__VA_ARGS__):(a))
#define _MAX_12(a,...) (((a)<_MAX_11(__VA_ARGS__))?_MAX_11(__VA_ARGS__):(a))
#define _MAX_13(a,...) (((a)<_MAX_12(__VA_ARGS__))?_MAX_12(__VA_ARGS__):(a))
#define _MAX_14(a,...) (((a)<_MAX_13(__VA_ARGS__))?_MAX_13(__VA_ARGS__):(a))
#define _MAX_15(a,...) (((a)<_MAX_14(__VA_ARGS__))?_MAX_14(__VA_ARGS__):(a))
#define _MAX_16(a,...) (((a)<_MAX_15(__VA_ARGS__))?_MAX_15(__VA_ARGS__):(a))
#define _MAX_17(a,...) (((a)<_MAX_16(__VA_ARGS__))?_MAX_16(__VA_ARGS__):(a))
#define _MAX_18(a,...) (((a)<_MAX_17(__VA_ARGS__))?_MAX_17(__VA_ARGS__):(a))
#define _MAX_19(a,...) (((a)<_MAX_18(__VA_ARGS__))?_MAX_18(__VA_ARGS__):(a))
#define _MAX_20(a,...) (((a)<_MAX_19(__VA_ARGS__))?_MAX_19(__VA_ARGS__):(a))
#define _MAX_21(a,...) (((a)<_MAX_20(__VA_ARGS__))?_MAX_20(__VA_ARGS__):(a))
#define _MAX_22(a,...) (((a)<_MAX_21(__VA_ARGS__))?_MAX_21(__VA_ARGS__):(a))
#define _MAX_23(a,...) (((a)<_MAX_22(__VA_ARGS__))?_MAX_22(__VA_ARGS__):(a))
#define _MAX_24(a,...) (((a)<_MAX_23(__VA_ARGS__))?_MAX_23(__VA_ARGS__):(a))
#define _MAX_25(a,...) (((a)<_MAX_24(__VA_ARGS__))?_MAX_24(__VA_ARGS__):(a))
#define _MAX_26(a,...) (((a)<_MAX_25(__VA_ARGS__))?_MAX_25(__VA_ARGS__):(a))
#define _MAX_27(a,...) (((a)<_MAX_26(__VA_ARGS__))?_MAX_26(__VA_ARGS__):(a))
#define _MAX_28(a,...) (((a)<_MAX_27(__VA_ARGS__))?_MAX_27(__VA_ARGS__):(a))
#define _MAX_29(a,...) (((a)<_MAX_28(__VA_ARGS__))?_MAX_28(__VA_ARGS__):(a))
#define _MAX_30(a,...) (((a)<_MAX_29(__VA_ARGS__))?_MAX_29(__VA_ARGS__):(a))
#define _MAX_31(a,...) (((a)<_MAX_30(__VA_ARGS__))?_MAX_30(__VA_ARGS__):(a))
#define _MAX_32(a,...) (((a)<_MAX_31(__VA_ARGS__))?_MAX_31(__VA_ARGS__):(a))
#define _MAX_33(a,...) (((a)<_MAX_32(__VA_ARGS__))?_MAX_32(__VA_ARGS__):(a))
#define _MAX_34(a,...) (((a)<_MAX_33(__VA_ARGS__))?_MAX_33(__VA_ARGS__):(a))
#define _MAX_35(a,...) (((a)<_MAX_34(__VA_ARGS__))?_MAX_34(__VA_ARGS__):(a))
#define _MAX_36(a,...) (((a)<_MAX_35(__VA_ARGS__))?_MAX_35(__VA_ARGS__):(a))
#define _MAX_37(a,...) (((a)<_MAX_36(__VA_ARGS__))?_MAX_36(__VA_ARGS__):(a))
#define _MAX_38(a,...) (((a)<_MAX_37(__VA_ARGS__))?_MAX_37(__VA_ARGS__):(a))
#define _MAX_39(a,...) (((a)<_MAX_38(__VA_ARGS__))?_MAX_38(__VA_ARGS__):(a))
#define _MAX_40(a,...) (((a)<_MAX_39(__VA_ARGS__))?_MAX_39(__VA_ARGS__):(a))
#define _MAX_41(a,...) (((a)<_MAX_40(__VA_ARGS__))?_MAX_40(__VA_ARGS__):(a))
#define _MAX_42(a,...) (((a)<_MAX_41(__VA_ARGS__))?_MAX_41(__VA_ARGS__):(a))
#define _MAX_43(a,...) (((a)<_MAX_42(__VA_ARGS__))?_MAX_42(__VA_ARGS__):(a))
#define _MAX_44(a,...) (((a)<_MAX_43(__VA_ARGS__))?_MAX_43(__VA_ARGS__):(a))
#define _MAX_45(a,...) (((a)<_MAX_44(__VA_ARGS__))?_MAX_44(__VA_ARGS__):(a))
#define _MAX_46(a,...) (((a)<_MAX_45(__VA_ARGS__))?_MAX_45(__VA_ARGS__):(a))
#define _MAX_47(a,...) (((a)<_MAX_46(__VA_ARGS__))?_MAX_46(__VA_ARGS__):(a))
#define _MAX_48(a,...) (((a)<_MAX_47(__VA_ARGS__))?_MAX_47(__VA_ARGS__):(a))
#define _MAX_49(a,...) (((a)<_MAX_48(__VA_ARGS__))?_MAX_48(__VA_ARGS__):(a))
#define _MAX_50(a,...) (((a)<_MAX_49(__VA_ARGS__))?_MAX_49(__VA_ARGS__):(a))
#define _MAX_51(a,...) (((a)<_MAX_50(__VA_ARGS__))?_MAX_50(__VA_ARGS__):(a))
#define _MAX_52(a,...) (((a)<_MAX_51(__VA_ARGS__))?_MAX_51(__VA_ARGS__):(a))
#define _MAX_53(a,...) (((a)<_MAX_52(__VA_ARGS__))?_MAX_52(__VA_ARGS__):(a))
#define _MAX_54(a,...) (((a)<_MAX_53(__VA_ARGS__))?_MAX_53(__VA_ARGS__):(a))
#define _MAX_55(a,...) (((a)<_MAX_54(__VA_ARGS__))?_MAX_54(__VA_ARGS__):(a))
#define _MAX_56(a,...) (((a)<_MAX_55(__VA_ARGS__))?_MAX_55(__VA_ARGS__):(a))
#define _MAX_57(a,...) (((a)<_MAX_56(__VA_ARGS__))?_MAX_56(__VA_ARGS__):(a))
#define _MAX_58(a,...) (((a)<_MAX_57(__VA_ARGS__))?_MAX_57(__VA_ARGS__):(a))
#define _MAX_59(a,...) (((a)<_MAX_58(__VA_ARGS__))?_MAX_58(__VA_ARGS__):(a))
#define _MAX_60(a,...) (((a)<_MAX_59(__VA_ARGS__))?_MAX_59(__VA_ARGS__):(a))
#define _MAX_61(a,...) (((a)<_MAX_60(__VA_ARGS__))?_MAX_60(__VA_ARGS__):(a))
#define _MAX_62(a,...) (((a)<_MAX_61(__VA_ARGS__))?_MAX_61(__VA_ARGS__):(a))
#define _MAX_63(a,...) (((a)<_MAX_62(__VA_ARGS__))?_MAX_62(__VA_ARGS__):(a))

#endif

