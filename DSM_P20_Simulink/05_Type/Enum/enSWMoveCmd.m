%% Create enSWMoveCmd enum

classdef enSWMoveCmd < Simulink.IntEnumType

    enumeration
        en_NULL(0)
        enUP_FORWARD(1)
        enDOWN_BACK(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSWMoveCmd.en_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '0���޶���&#10;1����ǰ&#10;2���º�,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
