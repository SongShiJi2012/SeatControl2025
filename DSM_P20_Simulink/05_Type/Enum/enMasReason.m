%% Create enMasReason enum

classdef enMasReason < Simulink.IntEnumType

    enumeration
        enNone(0)
        enPowerError(1)
        enRunError(2)
        enNodeError(3)
        enConfigError(4)
        enCarTypeError(5)
        enRecoverError(6)
        enPowerModeError(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMasReason.enNone;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '前置条件不满足原因&#10;0x0:enNone（无）&#10;0x1:enPowerError&#10;0x2:enRunError&#10;0x3:enNodeError&#10;0x4:enConfigError&#10;0x5:enCarTypeError&#10;0x6:enRecoverError&#10;0x6:enPowerModeError,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
