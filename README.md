# A fun exercise with probabilities

I came across this question a while ago and thought that it was a neat example of how to showcase the GNU scientific library in C. The question was:

*The probability of rain on a given calendar day in a city  is `p[i]`, where i is the day’s index. For example, `p[0]` is the probability of rain on January 1st, and `p[10]` is the probability of precipitation on January 11th. Assume the year has 365 days (i.e., `p` has 365 elements). What is the chance it rains more than `n` (e.g., 100) days? Write a function that accepts `p` (probabilities of rain on a given calendar day) and `n` as input arguments and returns the possibility of raining at least `n` days.*

The questions ask for the cumulative probability of rainy days in Vancouver exceeding an integer $n$ number of days. For this, we model the event of rain on a given day $i$ as a random variable (r.v.) following the Bernoulli distribution with probability $p_i$. The cumulative sum of $n$ days raining follows a Poisson binomial (PB) distribution. Then, let $X~PB$ be an r.v. to denote the probability of a given number of rainy days. We seek: 

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

Here's a helpful tip: when you're diving into exercises involving probabilities for less common distributions (like those that aren't normal or Poisson), you'll often find that there's a theoretical approach that can closely approximate your distribution with a normal distribution. So, before you jump into computing your probability directly, it's a good idea to look into the literature for a reasonable approximation. You might find it saves you some time and effort!

## GNU scientific library

The probabilities are computed using the GNU scientific library ([gsl](https://www.gnu.org/software/gsl/)) in the code. To use it, you need to install it first, which in Ubuntu can be done with the following:

```bash
sudo apt-get install libgsl-dev
```

After a successful installation, run the following command to inspect that the gsl packages where installed correctly:

```bash
dpkg -l | grep libgsl
```

## Compiling the code

To compile the code, you need to link with the gsl flags as well as the flag for the standard C math library ```libm```

```bash
gcc -O3 main.c -o main -lgsl -lgslcblas -lm
```
### Output
![Q1/Q1.jpg](https://github.com/lucasparada20/PicovoiceAssignment/blob/main/Q1/Q1.jpg)

