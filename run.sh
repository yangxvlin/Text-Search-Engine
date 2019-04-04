Make
date

a1.exe -t 1 -r 12 hello world > helloworld.txt
a1.exe -t 1 -r 99 algorithms are fun > algorithmsarefun.txt
a1.exe -t 1 -r 8 algorithms are fun > 0out-out1.txt

a1.exe -t 2 -r 12 hello world > helloworld-out2.txt
a1.exe -t 2 -r 99 algorithms are fun > algorithmsarefun-out2.txt
a1.exe -t 2 -r 8 algorithms are fun > 0out-out2.txt

# diff helloworld-out1.txt helloworld-out2.txt
# diff algorithmsarefun-out1.txt algorithmsarefun-out2.txt
# diff thecatisoutofthebag-out1.txt thecatisoutofthebag-out2.txt

date