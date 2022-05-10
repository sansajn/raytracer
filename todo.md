TODO:
 
- [ ] we can not set world object as a source for `AreaLight` (`set_object()` expect `unique_ptr`) and add it to the world (`add_object()` expect `*`)
- [ ] samplers can not be shared in Disk ojects (`set_sampler()` calls `map_samples` function changing sampler
- [ ] introduce logger library


Sampler architecture is all wrong e.g. `Lambertian` implementation use hemisphere samples, we need Sampler type which support only functionality we need.
