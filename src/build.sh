pushd ./ > /dev/null
cd ../build

gcc -o imana ../src/main.cpp

echo ""
echo ""
./imana

popd > /dev/null
