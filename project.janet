(declare-project
  :name "janet-md5"
  :description ```MD5 library wrapper for Janet ```
  :version "0.0.0")

(declare-native
  :name "md5/md5"
  :source @["c/module.c" "c/md5.c"])
