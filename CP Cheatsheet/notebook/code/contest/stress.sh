d=$1_fail
mkdir -p $d
for i in $(seq 1000); do
  ./gen $i > $d/in
  ./$1 < $d/in > $d/out
  ./brute < $d/in > $d/ans
  cmp -s $d/out $d/ans || {
    echo "test $i failed, see $d"
    exit
  }
done
rm -r $d
echo all passed
