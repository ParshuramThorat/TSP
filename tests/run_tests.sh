#
# TSP Testbench
# Runs tests

TEST_DIR=tests
TEST_COUNT=6
PROG=tsp
ARGS=

j=0
for i in `seq 1 $TEST_COUNT`; do
    echo -n "Running Test $i... "
    inp="inp-$i";
    outp_="out-${i}_";
    ./$PROG $ARGS < $TEST_DIR/$inp > $TEST_DIR/$outp_;
    diff -bBq $TEST_DIR/$outp $TEST_DIR/$outp_ > /dev/null;
    
done;
echo "Done Running"
