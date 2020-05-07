# GetIt

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://travis-ci.org/bartkessels/getit.svg?branch=development)](https://travis-ci.org/bartkessels/getit)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f9919567041d4715889d643b784e661f)](https://www.codacy.com/manual/bartkessels/getit?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=bartkessels/getit&amp;utm_campaign=Badge_Grade)

## Build application

```bash
$ cd build
$ cmake ../
$ make getit
$ ./bin/getit
```

## Run tests

```bash
$ cd build
$ cmake ../
$ make getit_tests
$ ./bin/getit_tests
```

### Dependencies

#### cpprestsdk

GetIt makes use of the [Microsoft CPP Rest SDK](https://github.com/Microsoft/cpprestsdk) library. Please checkout the documentation to see how you can [install](https://github.com/Microsoft/cpprestsdk#getting-started) this on your computer.
