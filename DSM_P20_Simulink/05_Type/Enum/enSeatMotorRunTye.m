%% Create enSeatMotorRunTye enum

classdef enSeatMotorRunTye < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_HUMEnable(1)
        EN_ComfortEnable(2)
        EN_MemoryEnable(3)
        EN_ManualEnable(4)
        EN_LearnEnable(5)
        EN_ResetEnable(6)
        EN_GearEnable(7)
        EN_ResEnable(8)
        EN_DiagIOEnable(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMotorRunTye.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节&#10;9：诊断IO控制,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
