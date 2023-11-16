cd GameofLife
wsl -d Arch bash docs.sh
cd ..
git add documentation.pdf
git commit -m "Exporting to zip"
git archive master -o GameofLife.zip