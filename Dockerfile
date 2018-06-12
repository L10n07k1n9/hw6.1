FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN g++ -g -o leo.hw6.1.finite.field.over.elliptic.curve.exe finite.field.over.ec.c
CMD ["./leo.hw6.1.finite.field.over.elliptic.curve.exe"]