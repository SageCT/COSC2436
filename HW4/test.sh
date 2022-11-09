cmd=hw4
if [ -f ${cmd} ]; then
    rm ${cmd}
fi

g++ -std=c++11 *.cpp -o ${cmd}

if [ ! -f ${cmd} ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi

for casenum in `seq 1 1 3`; do
    if [ -f ${casenum}.stderr ]; then
        rm ${casenum}.stderr
    fi
    if [ -f ${casenum}.stdcout ]; then
        rm ${casenum}.stdcout
    fi
done

for casenum in `seq 1 1 3`; do
	./${cmd} "input=input${casenum}.txt;output=output${casenum}.txt" 1>${casenum}.stdcout 2>${casenum}.stderr
	diff -iEBwu ans${casenum}.txt output${casenum}.txt > ${casenum}.diff
	if [ $? -ne 0 ]; then
    		echo -e "Test case ${casenum}    \033[1;91mFAILED.\033[0m"
	else
    		echo -e "Test case ${casenum}    \033[1;92mPASSED.\033[0m"
    		rm -f ${casenum}.diff
			rm -f ${casenum}.stderr
            rm -f ${casenum}.stdcout
	fi
done

