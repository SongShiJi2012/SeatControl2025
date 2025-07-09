%% Create enEngineType enum

classdef enEngineType < Simulink.IntEnumType

    enumeration
        EN_ENGINE_NONE(0)
        EN_ENGINE_CRANK(1)
        EN_ENGINE_RUNNING(2)
        EN_ENGINE_FAULT(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enEngineType.EN_ENGINE_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '·¢¶¯»ú×´Ì¬:&#10;0£ºnot running&#10;1£ºCRANK&#10;2£ºRUNNING&#10;3£ºFAULT,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
