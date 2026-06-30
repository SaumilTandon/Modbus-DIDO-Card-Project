idf_component_register(
    SRCS
        "main.c"
        "wifi_ap.c"
        "web_server.c"

    INCLUDE_DIRS
        "."

    EMBED_TXTFILES
        "../web/index.html"
        "../web/style.css"
        "../web/script.js"
)