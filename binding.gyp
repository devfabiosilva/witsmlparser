{
  "targets": [
    {
      "target_name": "witsml14xbson",
      "sources": [ "./nodejs/addon.c", "./stdsoap2.c" ],
      "include_dirs":[ "./include", "./" ],
      "library_dirs": ["./lib"],
      "libraries": [
              "-Wl,--start-group ../lib/libcws_js.a ../lib/libbson-shared-1.0.a ../parser/w1411/delete/delete1411ServerLib_shared.o ../parser/w1411/read/read1411ServerLib_shared.o ../parser/w1411/update/update1411ServerLib_shared.o ../parser/w1411/write/write1411ServerLib_shared.o -Wl,--end-group"
          ],
      "defines": ["CWS_LITTLE_ENDIAN", "WITH_STATISTICS", "WITH_NONAMESPACES"],
      "cflags": ["-Wno-stringop-truncation", "-Wno-format-truncation"],
    }
  ]
}

