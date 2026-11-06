# Eigenfluid / Navier–Stokes research

## Objective
Investigate a physically grounded, grid-free **velocity representation** for real-time 3D incompressible liquids. Implement in C++17 and Vulkan (SPIR-V compute), targeting sustained 60 FPS on baseline Apple M1 hardware. The goal is a measured research result, not a claim that modal fluids already outperform adaptive grid solvers.

## Established mathematical foundation
For a constant-density Newtonian incompressible fluid:

```text
∂u/∂t + (u·∇)u = -∇p/ρ + ν∇²u + f
∇·u = 0
```

Use divergence-free, domain-compatible Laplacian eigenfunctions Φ_i(x) and coefficients a_i(t):

```text
u(x,t) = Σ_i a_i(t) Φ_i(x)
-∇²Φ_i = μ_i Φ_i
```

Galerkin projection yields a small ODE system (sign conventions depend on the interaction definition):

```text
da_i/dt = -Σ_jk A_ijk a_j a_k - ν μ_i a_i + F_i
A_ijk = ∫Ω Φ_i · ((Φ_j·∇)Φ_k) dV
```

For a **fixed** domain and compatible divergence-free basis, pressure gradients vanish in the projected equations and incompressibility is enforced by construction. Nonlinear interactions still couple modes. A dense interaction tensor costs O(N³); symmetry, analytic selection rules and sparse representation are essential. See de Witt (2010, 2012) and Cui, Sen & Kim (2018).

## Main unsolved research step: actual liquid surfaces
Classic eigenfluids model flow in a fixed region, often smoke-like or fully occupied. Falling, pouring, impacting, and puddling liquid also require a **moving water–air interface**, topology changes, contact with solid objects, gravity, pressure and surface-tension boundary conditions. A level set φ(x,t)=0 is a possible continuous interface:

```text
∂φ/∂t + u·∇φ = 0
```

The moving boundary changes the admissible velocity space. Fixed-domain eigenfunctions alone do not conserve a freely moving liquid or impose the correct interface stresses. Study boundary-adapted/modal re-projection versus a localized conservative correction; neither is assumed efficient or accurate until demonstrated. Surface geometry could be an adaptive triangle mesh or an implicit function; **not using fluid particles does not prohibit geometric vertices or numerical quadrature**. See Sethian & Smereka (2003), and Jain et al. (2024) for alternative mesh-free boundary/pressure ideas.

## C++ / Vulkan architecture
- Physics module owns basis definitions, modal coefficients, forces, interaction coefficients, time integration, boundary/interface state and physical validation.
- Vulkan compute passes evolve modal state and eventually construct GPU-resident renderable surface geometry, without mandatory CPU readback.
- The generic `vulkan-systems/gpu` API manages resources, pipelines, dispatches and barriers. `vulkan-systems/render` consumes GPU buffers and materials, independent of the fluid solver.
- Expose no fluid-specific hooks from the generic GPU/renderer. Keep solver independent of swapchain, camera and lighting.

## Optimization hypotheses to test
1. Compare 32/64/128/256 modes against a trusted reference, tracking numerical error versus runtime.
2. Precompute exact/analytic sparse interactions where possible. Preserve nonlinear coupling and avoid unprincipled truncation.
3. Compare CPU coefficient integration with Vulkan GPU sparse-interaction reductions; small mode counts might favor CPU.
4. Test energy-aware/skew-symmetric interaction formulations and stable timestep integrators. Record both physical viscous dissipation and numerical dissipation.
5. Cache/reuse evaluations, exploit transforms for bulk sampling, bound surface-work cost and avoid host/GPU synchronization stalls.
6. Profile complete frames and energy/volume/convergence errors on a physical Apple M1; the 60 FPS target is **not verified**.

## Minimum validation
- Fixed-box analytic/known flows; divergence-free field and no-penetration boundaries.
- Unforced inviscid energy and momentum behavior; viscous decay against expected rates.
- Forces and moving obstacles with consistent boundary work.
- Moving-surface advection, bounded mass/volume error, topology changes and contact.
- Falling glass: rest → free fall → impact/ejection → spreading puddle.
- Compare accuracy and performance to a conventional adaptive 3D liquid solver. Failures must be reported, not hidden by visually convincing shading.

## Research references
See `papers/` for the six papers and original full-text/DOI links. These are reference notes, not PDFs stored in the repository.
