# Finite Time Blowup for Navier–Stokes (2026)
OpenAI, September 8, 2026.

[Original research paper (PDF)](https://cdn.openai.com/pdf/32d9f210-8b73-45e0-91bc-82a30aef8a9a/navier-stokes.pdf)
[OpenAI research announcement](https://openai.com/index/navier-stokes-solution/)
[Clay Mathematics Institute announcement (11 September 2026)](https://www.claymath.org/news/navier-stokes-announcement/)

OpenAI presents a mathematical construction of finite-time unbounded velocity in smooth, externally forced, three-dimensional incompressible Navier–Stokes flow with bounded total kinetic energy. Clay describes the announced resolution as apparently settled while its formal process continues.

Relevance to this C++/Vulkan eigenfluid project:
- Not a faster numerical solver or a new rendering method.
- Concentrating vortices can place significant unresolved dynamics at arbitrarily small spatial scales; finite modal truncation needs explicit error and high-mode energy monitoring.
- Validate local maxima, vorticity gradients, spectral tail energy, timestep sensitivity and convergence, not only total kinetic energy.
- Adaptive mode selection/local refinement is an optimization hypothesis, not a demonstrated consequence of the proof.
- The constructed forced singular flow does not predict typical free-surface water behavior; it does not solve our moving-interface or wall-boundary problem.
