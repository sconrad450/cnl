# Contributing to CNL

Contributions are more than welcome! Not only is there a lot of code to be written and maintained, 
but user feedback is much appreciated as CNL is 99% API over existing language functionality.

## Submitting Issues

Feel free to [add an issue](https://github.com/johnmcfarlane/cnl/issues/) via GitHub or 
[contact me directly](https://github.com/johnmcfarlane)
([cnl.contributing@john.mcfarlane.name](cnl.contributing@john.mcfarlane.name)).

There is no issue template. Please just try to be as clear as possible. Formatting with 
markdown is appreciated (see below). Bugs submitted in the form of pull requests with failing tests
are the best way to submit an issue. (See below for details on pull requests.)

## Markdown

Being a GitHub project, I lean toward formatting with [GitHub flavored 
markdown](https://github.github.com/gfm/) but [CommonMark](https://commonmark.org/) is great too.

Files are not computer code. Do not format them as such. Use emphasis instead, e.g.: "To use 
`cnl::fixed_point`, include *cnl/fixed_point.h*".

## Pull Requests

Pull requests should be made against the [develop branch](https://github.com/johnmcfarlane/cnl).
When writing commit messages, please [respect the wishes](https://chris.beams.io/posts/git-commit/)
of out Git overlords. Single-commit PRs will be rebased. Multi-commit PRs will be merged. PRs 
should achieve one coherent *thing* or enhance the library in on single *way*. Changes in pursuit 
of that one thing should probably be different commits in the same PR. Public-facing APIs should be
accompanied by tests. (See below.) All commits should pass all tests on all targets (but I'm 
unlikely to notice provided all CI results are green.)

When writing commit messages, assume the *cnl* directory and the `cnl` namespace, e.g.:

> Move _impl::is_fixed_point into its own header
>  
> * _impl/fixed_point/is_fixed_point

As you can see, I like to bullet the details of a commit message after the headline but in general,
go easy on the markdown in commit messages. They're rarely parsed that way.

## Tests

Please use the contents of [src/test](https://github.com/johnmcfarlane/cnl/blob/develop/src/test/) 
as an example of how to write CNL tests. It's a little chaotic in there (sorry) so look at newer 
commit when determining what example to follow. Prefer `static_assert` tests to run-time tests, try
and keep source files small and dedicted to a single library component of combination of 
components. Follow the project directory structure and code style. (See below.)

## Directory Structure

### *include* directory

This is the library include directory. Client code is expected to add it to their system search 
paths (e.g. with `-isystem`) and include the files in [include/cnl](include/cnl). The coverall 
header, [include/cnl/all.h](include/cnl/all.h), should contain most top-level, public-facing APIs
and is intended to be included:

```C++
#include <cnl/all.h>
```

The exception is the content of [include/cnl/auxiliary](include/cnl/auxiliary) which contains 
experimental integration (glue) code for other 3rd-party libraries and which must be pulled in
explicitly.

The contents of [include/cnl/_impl](include/cnl/_impl) and off-limits to library users. The rule 
for the *_impl* directory is that if 

## Code Style

### Namespaces

Full qualify identifiers in *src*. The exceptions are `cnl::_impl::identical` and 
`cnl::_impl::assert_same` which are never the subjects of tests. Keep things out of the global 
namespace where possible. Wrap individual compile-time tests in a separate `test_some_feature` as
exemplified throughout most of the test suite.

Minimally qualify identifiers in source files containted under the *include/cnl* directory. The 
exception is when ADL is expected to be a problem.

## Communication

I am happy to try and communicate in any language but I speak only English well enough to develop 
software. So if you have good English, you will get far more sense with me by using it. 
Many developers have to learn the idiosyncracies of the language just to get stuff done.
Most often, they learned American English. It's not my preferred dialect. 
But it's the lingua franca of the computing world.
 
Out of a respect and admiration for those poor people I ask that the content CNL work be done in American English.
I only have to imagine if I the problems they have had had had.
