g++ myCode.cpp -std=c++17 -o myCode.out
g++ correctCode.cpp -std=c++17 -o correctCode.out
g++ generator.cpp -std=c++17 -o generator.out

ok=0;

for i in `seq 1 1000`
do
    echo $i > tmp
    ./generator.out < tmp > test
    ./correctCode.out < test > correctRet
    ./myCode.out < test > myRet
    diff myRet correctRet > /dev/null
    if [ $? == 0 ]
    then
        ((ok++))
    else
        echo "Wrong answer on test $i"
        echo "Test"
        ./generator.out < tmp
        echo "Output"
        ./myCode.out < test
        echo "Answer"
        ./correctCode.out < test
        break
    fi
done
if [ $ok == 1000 ]
then
    echo ACCEPTED
fi