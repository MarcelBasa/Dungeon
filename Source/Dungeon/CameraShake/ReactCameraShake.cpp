#include "ReactCameraShake.h"

UReactCameraShake::UReactCameraShake()
{
    OscillationDuration = 10.f;
    OscillationBlendInTime = 10.f;
    OscillationBlendOutTime = 10.f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(5.0f, 10.0f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 35.0f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(5.0f, 10.0f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 35.0f);
}