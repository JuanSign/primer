d=$1_fail
c="cmp -s $d/out $d/ans"
[ "$2" ] && c="./$2 $d/in $d/out $d/ans"
mkdir -p $d
for i in $(seq 1000); do
  ./gen $i > $d/in
  ./$1 < $d/in > $d/out
  ./brute < $d/in > $d/ans
  $c || {
    echo "test $i failed, see $d"
    exit
  }
done
rm -r $d
echo all passed
