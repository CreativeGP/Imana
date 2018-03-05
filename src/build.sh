pushd ./ > /dev/null
cd ../build

g++ -std=c++14 -g -o imana ../src/main.cpp ../src/numerical_formula/fraction.cpp \
&& echo "" \
&& echo "" \
&& ./imana

popd > /dev/null
