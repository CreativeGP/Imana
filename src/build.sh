pushd ./ > /dev/null
cd ../build

make \
&& echo "" \
&& echo "" \
&& ./imana

popd > /dev/null
