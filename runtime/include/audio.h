/**
 * @file audio.h
 * @brief GameBoy Audio Processing Unit definitions
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "gbrt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Public Interface
 * ========================================================================== */

/**
 * @brief Create audio subsystem state
 */
void* gb_audio_create(void);

/**
 * @brief Destroy audio subsystem state
 */
void gb_audio_destroy(void* apu);

/**
 * @brief Reset audio state
 */
void gb_audio_reset(void* apu);

/**
 * @brief Read from audio register
 */
uint8_t gb_audio_read(GBContext* ctx, uint16_t addr);

/**
 * @brief Write to audio register
 */
void gb_audio_write(GBContext* ctx, uint16_t addr, uint8_t value);

/**
 * @brief Step audio subsystem
 */
void gb_audio_step(GBContext* ctx, uint32_t cycles);

/**
 * @brief Reset Frame Sequencer (called on DIV write)
 */
void gb_audio_div_reset(void* apu);

/**
 * @brief Get current sample for left/right channels
 * @param apu Audio state
 * @param left Pointer to store left sample
 * @param right Pointer to store right sample
 */
void gb_audio_get_samples(void* apu, int16_t* left, int16_t* right);

/* For ports: bit n set silences channel n+1 in the mix; the hook, when set,
 * adds the port's own audio to each output sample (left/right before the
 * high-pass filter, in the same scale: 16-bit full range; vol_l/vol_r are
 * NR50's master volumes 0-7, so the added audio can follow the game's fades). */
extern uint8_t gb_audio_mute_mask;
extern void (*gb_audio_mix_hook)(int* left, int* right, int vol_l, int vol_r);

#ifdef __cplusplus
}
#endif

#endif /* AUDIO_H */
