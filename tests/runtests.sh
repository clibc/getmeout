RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

for FILE in *;
do
    if [ "$FILE" == "runtests.sh" ];
    then
        continue
    fi
       
    result=`../a.out $FILE > /dev/null`
    if [ $? == 0 ];
    then
        echo -e "${GREEN} [*] Passed $FILE ${NC}"
    else
        echo -e "${RED} [x] Failed $FILE ${NC}"
    fi
done

rm out*
