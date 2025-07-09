%% Create enPowerModeSts enum

classdef enPowerModeSts < Simulink.IntEnumType

    enumeration
        EN_OFF(0)
        EN_ACC(1)
        EN_ON(2)
        EN_CRANK(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enPowerModeSts.EN_OFF;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'µçÔ´µµÎ»×´Ì¬&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
