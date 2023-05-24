# Corecpp 2023 allocations tracking [lighting talk](https://www.meetup.com/corecpp/events/293582735/)

## Repository structure
Every folder in the repository represents one snippet. Each snippet should be buildable in the container described by the Dockerfile in the root of the repository.

To build and attach to the container, invoke the following command in the root of the repository.
```(bash)
> make build
> make run
```

To run a snippet. In the container.
```(bash)
> /workdir# cd tcmallochook/
> /workdir/tcmallochook# make build 
clang++ -std=c++20 -Wall -Wextra -O2 -DNDEBUG -ltcmalloc hook.cpp -o hook 
> /workdir/tcmallochook# make run
./hook
malloc(32} called from 0x11940a0
sizeof(std::string) = 32
abacaba
```

## Snippets Description

### glibcmalloc and tcmalloc

These are snippets of a trivial malloc benchmark, created to provide an estimate of the order of magnitude of malloc+free call latency.

The actual latency in a real-world application will depend on the usage pattern. Please note that this benchmark should not be considered extensive or representative in any way. Its purpose is to provide a general understanding, rather than being a comprehensive benchmark.

### glibchook

This snippet demonstrates the usage of `__mallok_hook` from glibc. It's worth noting that this snippet is a bit outdated, as `__malloc_hooks` have been deprecated and removed from glibc. However, it serves as an interesting idea.

### tcmallochook

This snippet showcases hooks based on tcmalloc. It works well, but it requires gperftools to function properly.

Please be aware that using hooks can have significant implications for latency, so they should not be utilized in a production environment.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.

## Disclaimer

This project is not an official Google project. It is not supported by
Google and Google specifically disclaims all warranties as to its quality,
merchantability, or fitness for a particular purpose.
