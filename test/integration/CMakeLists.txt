add_test(NAME integration_ReconstructedParticle
         COMMAND python "${CMAKE_CURRENT_LIST_DIR}/ReconstructedParticle.py")

       add_test(NAME integration_ReconstructedParticleSource
         COMMAND python "${CMAKE_CURRENT_LIST_DIR}/ReconstructedParticleSource.py")
