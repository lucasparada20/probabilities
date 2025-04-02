# A fun exercise with probabilities

I came across this question a while ago and thought that it was a neat example of how to showcase the GNU scientific library in C. The question was:

*The probability of rain on a given calendar day in Vancouver is `p[i]`, where i is the day’s index. For example, `p[0]` is the probability of rain on January 1st, and `p[10]` is the probability of precipitation on January 11th. Assume the year has 365 days (i.e., `p` has 365 elements). What is the chance it rains more than `n` (e.g., 100) days in Vancouver? Write a function that accepts `p` (probabilities of rain on a given calendar day) and `n` as input arguments and returns the possibility of raining at least `n` days.*

The questions ask for the cumulative probability of rainy days in Vancouver exceeding an integer $n$ number of days. For this, we model the event of rain on a given day $i$ as a random variable (r.v.) following the Bernoulli distribution with probability $p_i$. The cumulative sum of $n$ days raining follows a Poisson binomial (PB) distribution. Then, let $X~PB$ be an r.v. to denote the probability of a given number of rainy days. We seek 

```math
P(X > n) = 1 - P(X\leq n)
```

From this [article](https://epubs.siam.org/doi/abs/10.1137/1140093), we know that $P(X\leq n)$ can be approximated with a transformation from the standard normal distribution with the following $z$ score, which means truncating off the negative-valued probabilities of the normal distribution:

```math
z = \Phi\left(\frac{X + 0.5 - \mu}{\sigma}\right)
```

The transformation is then for a $z \sim N(0,1)$:

```math
P(z \leq n) ≈ max \left(0, g(z)\right).
```
Where: $g(z) = \Phi(z) + \gamma(1-z^2)\frac{\phi(z)}{6}$ and $\gamma=\frac{1}{\sigma^3}\sum_{i}p_i(1-p_i)(1-2p_i)$.

The probabilities are computed using the GNU scientific library (gsl) in the code, which I used in the first project of my dissertation (the cumulative probability of customer demands exceeding an integral vehicle capacity).

## Compiling the code

As mentioned earlier, the code requires the gsl. In Ubuntu, it can be downloaded and installed with:

```bash
sudo apt-get install libgsl-dev
```

Then, compile the code and link gsl as follows:

```bash
gcc -O3 main.c -o main -lgsl -lgslcblas -lm
```
### Output
![Q1/Q1.jpg](https://github.com/lucasparada20/PicovoiceAssignment/blob/main/Q1/Q1.jpg)

