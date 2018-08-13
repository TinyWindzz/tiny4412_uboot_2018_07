echo -e "\033[45m start fusing \033[0m"

cd sd_fuse/tiny4412/
./sd_fusing.sh /dev/sdb
cd ../..

echo -e "\033[45m fusing over \033[0m"
