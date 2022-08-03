# scheme_lexical_analyzer🧞‍♀️

![Unknown](https://user-images.githubusercontent.com/68461123/182498022-83ccb134-8dda-4365-bf1f-2d1c204020f3.jpeg)

## What is this?

This is a lexical analyzer made with C++ for [Scheme](https://en.wikipedia.org/wiki/Scheme_(programming_language)) programming language, **multithreaded-optimized**!🧞♀️

## But how does it work tho

Tokenization is the first step in compiling code. What is tokenization you ask? It's basically to match each word in the code with one of the defined so-called "tokens". this allows for later more complex analysis. The process of lexical analysis allows for error catching in the code, where the code input is not matching a defined token or does not follow the defined rules.
It works by using defined states in a table, where you define for each state, which other states is it allowed to go from the current state.

For example:

It is valid that, for every number (0,1,2,3,4,5,6,7,8,9) you can go to every other number to generate an **INT**, also you can go from the **INT** state to a **FLOAT** state by transitioning with a ".", and that's how different tokens are matched and how transitions are made from state to state by different inputs.

## How is this helpful?

There are far better and standarized implementations for lexical analysis in programming languages (see *[Flex](https://www.geeksforgeeks.org/flex-fast-lexical-analyzer-generator)), but the main idea should be the same. This was made for educational purposes!  🐝

![cat](https://media.giphy.com/media/o0vwzuFwCGAFO/giphy.gif)

made with love
