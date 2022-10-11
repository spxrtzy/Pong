struct wininfo {
    int width;
    int height;
    int framesps;
    char *title;

};

struct paddle {
    int x;
    int y;
    int width;
    int height;
    int speed;
};

struct ball {
    int x;
    int y;
    float radius;
    int speedY;
    int speedX;
};


