(import md5/md5)

(defn hex [buf]
  (->> buf
       (map (fn [ch] (string/format "%02x" ch)))
       (string/join)))

(let [ctx (md5/init)
      buf (buffer/new 0)]
  (buffer/push-string buf "The quick brown fox jumps over the lazy dog")
  (md5/update ctx buf)
  (let [result (-> (md5/final ctx)
                   (buffer/slice))]
    (assert (= (hex result) "9e107d9d372bb6826bd81d3542a419d6"))))

(let [ctx (md5/init)
      buf (buffer/new 0)]
  (buffer/push-string buf "The quick brown fox jumps over the lazy dog.")
  (md5/update ctx buf)
  (let [result (-> (md5/final ctx)
                   (buffer/slice))]
    (assert (= (hex result) "e4d909c290d0fb1ca068ffaddf22cbd0"))))
