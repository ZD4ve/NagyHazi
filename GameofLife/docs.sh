if ! doxygen; then
    rm latex -r
    exit 1
fi
cd latex
make pdf
cd ..
mv latex/refman.pdf "../Code documentation.pdf"
rm latex -r