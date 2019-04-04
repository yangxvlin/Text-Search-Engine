PATH_OUT="outputs/"
PATH_SAMPLE="samples/"
SORT_SUFFIX="-sorted"
DIFF_SUFFIX="diff"
TXT_SUFFIX=".txt"

CAT="catoutofbag-8"
ALG="algorithms-99"
HEL="helloworld-12"


sort $PATH_OUT$CAT$TXT_SUFFIX > $PATH_OUT$CAT$SORT_SUFFIX$TXT_SUFFIX
sort $PATH_OUT$ALG$TXT_SUFFIX > $PATH_OUT$ALG$SORT_SUFFIX$TXT_SUFFIX
sort $PATH_OUT$HEL$TXT_SUFFIX > $PATH_OUT$HEL$SORT_SUFFIX$TXT_SUFFIX

sort $PATH_SAMPLE$CAT$TXT_SUFFIX > $PATH_SAMPLE$CAT$SORT_SUFFIX$TXT_SUFFIX
sort $PATH_SAMPLE$ALG$TXT_SUFFIX > $PATH_SAMPLE$ALG$SORT_SUFFIX$TXT_SUFFIX
sort $PATH_SAMPLE$HEL$TXT_SUFFIX > $PATH_SAMPLE$HEL$SORT_SUFFIX$TXT_SUFFIX

echo "diff for cat"
diff $PATH_OUT$CAT$SORT_SUFFIX$TXT_SUFFIX $PATH_SAMPLE$CAT$SORT_SUFFIX$TXT_SUFFIX #> $PATH_OUT$CAT$DIFF_SUFFIX$TXT_SUFFIX
echo "diff for alg"
diff $PATH_OUT$ALG$SORT_SUFFIX$TXT_SUFFIX $PATH_SAMPLE$ALG$SORT_SUFFIX$TXT_SUFFIX #> $PATH_OUT$ALG$DIFF_SUFFIX$TXT_SUFFIX
echo "diff for hel"
diff $PATH_OUT$HEL$SORT_SUFFIX$TXT_SUFFIX $PATH_SAMPLE$HEL$SORT_SUFFIX$TXT_SUFFIX #> $PATH_OUT$HEL$DIFF_SUFFIX$TXT_SUFFIX