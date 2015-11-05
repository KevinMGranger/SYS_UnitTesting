# README

PLEASE run without debugging (Ctrl+F5), so that the console window stays
open, and you can see the output.

# What framework did you use?

I chose to use [Catch](https://github.com/philsquared/Catch).

# What steps did you need to take in order to make it work?

I had to download the single header file and include it in my project.

Really, that's it!

# Was it intuitive?

Very! It's almost like writing plain english!

# Would you recommend this framework to other people?

Yes, and I already have.

# Is the framework well documented?

Yes! To quote the README from it, "The documentation will continue until morale improves"

# What problems did you have with unit testing?

Figuring out how to generate data for multiple test cases is a bit of a pain.

I'm not sure if Catch supports that very well. Perhaps I should write a custom
test-runner?

# Describe the code and the tests.

There are two transform implementations. One tracks rotations via an axis and an angle,
and one tracks rotations via a quaternion. These are implementation details that shouldn't
affect the interface, so it's the perfect candidate for unit testing.


I test that two (theoretically) equivalent transforms:

- produce approximately equivalent world matrices, and that

- these matrices transform points approximately equivalently, and

- do the above even after being mutated (rotated further).


What could be improved:

- many more permutations of data!
(Catch doesn't have generation yet, but they're working on it)

- testing after other mutations and combinations thereof

- parallelization (if I'm not afraid to copy around data,
this is an emberassingly parallel problem)

- true unit testing.

In a proper unit test, you'd have a list of inputs and known proper outputs.

The two implementations would then be given those inputs and run through
the same operations, and have their outputs compared to the known good values.

Because of the difficulty of computing this on my own (and the relative
simplicity of each transform implementation), I opted to compare the two, since
I would be getting known good values from them anyway to start with.


Note: When implementing the two, I validated by eye that they were mostly
equivalent at first. However, I spend an hour trying to figure out why I saw
radically different values-- only to realize later that -5*10^-8 is roughly
the same as 1*10^-7 ! If I had written my tests first (as Test Driven
Development advises), I would not have had this issue!
