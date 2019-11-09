ARG QEMU_PLATFORM
FROM balenalib/${QEMU_PLATFORM}-debian-golang
ARG QEMU_PLATFORM
ARG GITHUB_OAUTH_TOKEN
ARG PROJECT_USERNAME
ARG PROJECT_REPONAME
ARG SHA1
ARG VERSION
ADD . $GOPATH/src/github.com/fibercrypto/libskycoin/

RUN [ "cross-build-start" ]

RUN sh $GOPATH/src/github.com/fibercrypto/libskycoin/ci-scripts/docker_install_debian.sh
RUN make -C $GOPATH/src/github.com/fibercrypto/libskycoin dep
RUN go get github.com/gz-c/gox
RUN go get -t ./...
ENV CGO_ENABLED=1
ENV ARCH=${QEMU_PLATFORM}
ENV OS="Linux"
RUN make -C $GOPATH/src/github.com/fibercrypto/libskycoin build
RUN tar -czf libskycoin-${VERSION}-${OS}-${ARCH}.tar.gz -C $GOPATH/src/github.com/fibercrypto/libskycoin/build $GOPATH/src/github.com/fibercrypto/libskycoin/build/*
RUN go get github.com/tcnksm/ghr
RUN ghr -t ${GITHUB_OAUTH_TOKEN} -u ${PROJECT_USERNAME} -r ${PROJECT_REPONAME} -c ${SHA1} -replace -draft ${VERSION} libskycoin-${VERSION}-${OS}-${ARCH}.tar.gz

RUN [ "cross-build-end" ]